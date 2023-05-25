#include "../headers/renderEngine.hpp"

#include "../../../tools/tracy/tracy/Tracy.hpp"

RenderEngine::RenderEngine(const Vector<int>& size, const std::string& name) {
  // Initalize GLFW
  if (!glfwInit()) {
    throw std::runtime_error("ERROR: Couldn't Initialize GLFW...");
  }

  // Create a window and set the context
  this->window_ = glfwCreateWindow(size.x, size.y, name.c_str(), NULL, NULL);
  glfwMakeContextCurrent(this->window_);

  // Initialize GLEW
  GLuint errCode = glewInit();
  if (errCode != GLEW_OK) {
    glfwTerminate();
    throw std::runtime_error("Error: Unable to Initialize GLEW...");
  }

  // Get Versions
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << "\nOpenGL version supported "
            << version << std::endl;

  // Draw pixels if close to the viewer
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  this->meshes_ = new std::vector<Mesh*>();
  this->shaders_ = new std::map<std::string, Shader*>();
  this->shaderNames_ = new std::vector<std::string>();
  this->shaderCompiler_ = new ShaderCompiler();
}

RenderEngine::~RenderEngine() {
  for (unsigned int i = 0; i < this->meshes_->size(); i++) {
    delete this->meshes_->at(i);
  }
  delete this->meshes_;
  for (unsigned int i = 0; i < this->shaderNames_->size(); i++) {
    delete this->shaders_->at(this->shaderNames_->at(i));
  }
  delete this->shaders_;
  delete this->shaderNames_;
  delete this->shaderCompiler_;

  glfwTerminate();
}

void RenderEngine::Draw(const glm::mat4x4* const orthoViewMatrix) {
  ZoneScopedN("RenderEngine::Draw");
  //* Clear Drawing Surface
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //* Draw Calls
  std::string shaderName = "default";
  Shader* shader = this->shaders_->at("default");
  shader->Use();
  for (unsigned int i = 0; i < this->meshes_->size(); i++) {
    // Load Active Shader
    if (shaderName != this->meshes_->at(i)->GetShaderName()) {
      shaderName = this->meshes_->at(i)->GetShaderName();
      if (this->shaders_->count(shaderName) > 0) {
        shader = this->shaders_->at(shaderName);
      } else {
        shader = this->shaders_->at("default");
      }
      shader->Use();
    }

    // Update Uniforms
    ZoneScopedN("RenderEngine::Draw::UpdateMVP");
    glm::mat4x4 mvp =
        *(orthoViewMatrix) * *(this->meshes_->at(i)->GetModelMatrix());
    shader->PassUniformMatrix("mvp", &mvp);
    shader->PassUniform3f("color", this->meshes_->at(i)->GetColor());

    this->meshes_->at(i)->Draw();
  }

  // put the stuff we've been drawing onto the display
  glfwSwapBuffers(this->window_);
}

Mesh* RenderEngine::AddMesh(Mesh* mesh) {
  this->meshes_->push_back(mesh);
  return mesh;
}

void RenderEngine::CompileShader(const std::string& vertex,
                                 const std::string& fragment,
                                 const std::string& name) {
  if (this->shaders_->count(name) > 0) {
    throw std::runtime_error("ERROR: Shader with name " + name +
                             " already exists!");
  }

  Shader* shader = new Shader(this->shaderCompiler_, vertex, fragment);
  this->shaderNames_->push_back(name);
  this->shaders_->insert(std::pair<std::string, Shader*>(name, shader));
}

Shader* const RenderEngine::GetShader(const std::string& name) {
  if (this->shaders_->count(name) > 0) {
    return this->shaders_->at(name);
  } else {
    throw std::runtime_error("ERROR: Shader with name " + name +
                             " doesn't exist!");
  }
}

GLFWwindow* const RenderEngine::GetWindow() const noexcept {
  return this->window_;
}
