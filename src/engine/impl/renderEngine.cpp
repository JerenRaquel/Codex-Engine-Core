#include "../headers/renderEngine.hpp"

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

  this->quads_ = new std::vector<Quad*>();
  this->shaders_ = new std::map<std::string, Shader*>();
  this->shaderNames_ = new std::vector<std::string>();
  this->shaderCompiler_ = new ShaderCompiler();
}

RenderEngine::~RenderEngine() {
  for (unsigned int i = 0; i < this->quads_->size(); i++) {
    delete this->quads_->at(i);
  }
  delete this->quads_;
  for (unsigned int i = 0; i < this->shaderNames_->size(); i++) {
    delete this->shaders_->at(this->shaderNames_->at(i));
  }
  delete this->shaders_;
  delete this->shaderNames_;
  delete this->shaderCompiler_;

  glfwTerminate();
}

void RenderEngine::Draw(const Camera* camera) {
  //* Clear Drawing Surface
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pass the Ortho and View Matrix to each shaders
  for (unsigned int i = 0; i < this->shaderNames_->size(); i++) {
    Shader* shader = this->shaders_->at(this->shaderNames_->at(i));
    shader->Use();
    shader->PassUniformMatrix("ortho", camera->GetOrthoMatrix());
    shader->PassUniformMatrix("view", camera->GetViewMatrix());
  }

  //* Draw Calls
  for (unsigned int i = 0; i < this->quads_->size(); i++) {
    // Load Active Shader
    std::string shaderName = this->quads_->at(i)->GetShaderName();
    Shader* shader;
    if (this->shaders_->count(shaderName) > 0) {
      shader = this->shaders_->at(shaderName);
    } else {
      shader = this->shaders_->at("default");
    }

    shader->Use();

    // Update Uniforms
    shader->PassUniformMatrix("model", this->quads_->at(i)->GetModelMatrix());
    shader->PassUniform3f("color", this->quads_->at(i)->GetColor());

    this->quads_->at(i)->Draw();
  }

  // put the stuff we've been drawing onto the display
  glfwSwapBuffers(this->window_);
}

Quad* RenderEngine::AddQuad(Quad* quad) {
  this->quads_->push_back(quad);
  return quad;
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
