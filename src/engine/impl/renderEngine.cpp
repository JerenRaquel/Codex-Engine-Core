#include "../headers/renderEngine.hpp"

#include "Tracy.hpp"

void RenderEngine::InitOpenGL(const Vector2<int>& size,
                              const std::string& name) {
  // Initalize GLFW
  if (!glfwInit()) {
    throw std::runtime_error("ERROR: Couldn't Initialize GLFW...");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

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
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  // Initialize GUI
  this->guiManager_ = new GuiManager(this->window_);
}

void RenderEngine::RenderMeshBatch(
    const glm::mat4x4& cameraMatrix,
    std::vector<MeshRenderData*>* const meshRenderData) const noexcept {
  ZoneScopedN("RenderEngine::RenderMeshBatch");
  //* Draw Calls
  Shader* shader = nullptr;
  for (unsigned int i = 0; i < meshRenderData->size(); i++) {
    MeshRenderData* data = meshRenderData->at(i);
    if (!data->shouldRender_) continue;

    std::string meshType = data->GetMeshType();
    if (this->meshTypes_->count(meshType) == 0) continue;

    // Load Active Shader
    const std::string shaderName = data->GetMaterial()->GetShaderName();
    if (this->shaders_->count(shaderName) > 0) {
      shader = this->shaders_->at(shaderName);
    } else {
      shader = this->shaders_->at("default");
    }
    shader->Use();

    // Pass Uniforms
    data->PassUniforms(shader, cameraMatrix);

    // Draw
    this->meshTypes_->at(meshType)->Draw();
    data->UnbindTexture();
  }
}

void RenderEngine::RenderTextBatch(
    std::vector<TextRenderData*>* const textRenderData) const noexcept {
  Shader* shader = this->shaders_->at(this->defaultTextShaderName_);
  shader->Use();
  shader->PassUniformMatrix("projection", this->textHandler_->GetOrthoMatrix());

  for (unsigned int i = 0; i < textRenderData->size(); i++) {
    TextRenderData* data = textRenderData->at(i);
    shader->PassUniform3f("textColor", data->color_);
    this->textHandler_->DrawText(data->GetText(), data->GetPosition(),
                                 data->GetScale());
  }
}

RenderEngine::RenderEngine(const Vector2<int>& size, const std::string& name,
                           const std::string& defaultFontFile,
                           const std::string& textShaderName)
    : defaultTextShaderName_(textShaderName) {
  // Setup OpenGL Window Context
  this->InitOpenGL(size, name);

  this->shaders_ = new std::map<std::string, Shader*>();
  this->shaderNames_ = new std::vector<std::string>();
  this->shaderCompiler_ = new ShaderCompiler();
  this->textHandler_ = new TextHandler(defaultFontFile, size);
  this->meshTypes_ = new std::map<std::string, Mesh*>();
}

RenderEngine::~RenderEngine() {
  for (unsigned int i = 0; i < this->shaderNames_->size(); i++) {
    delete this->shaders_->at(this->shaderNames_->at(i));
  }
  delete this->shaders_;
  delete this->shaderNames_;
  delete this->shaderCompiler_;
  delete this->textHandler_;
  for (auto mesh : *(this->meshTypes_)) {
    delete mesh.second;
  }
  delete this->meshTypes_;
  delete this->guiManager_;
  glfwTerminate();
}

void RenderEngine::Render(Camera* const camera,
                          const Scene* const scene) const noexcept {
  //* Clear Drawing Surface
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  this->guiManager_->NewFrame();

  if (scene != nullptr) {
    //* Render UI
    this->RenderTextBatch(scene->GetTextRenderDataPointer());

    //* Render Meshes
    glm::mat4x4 cameraMatrix =
        *(camera->GetOrthoMatrix()) * *(camera->GetOriginalViewMatrix());
    this->RenderMeshBatch(cameraMatrix, scene->GetMeshUIRenderDataPointer());

    //* Render Meshes
    this->RenderMeshBatch(*(camera->GetViewOrthoMatrix()),
                          scene->GetMeshRenderDataPointer());
  }

  this->guiManager_->Display();
  this->guiManager_->Render();

  //* Swap Buffers
  glfwSwapBuffers(this->window_);
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

void RenderEngine::AddMeshType(const std::string& name, Mesh* const mesh) {
  if (this->meshTypes_->count(name) > 0) {
    throw std::runtime_error("ERROR: Mesh with name " + name +
                             " already exists!");
  }
  this->meshTypes_->insert(std::pair<std::string, Mesh*>(name, mesh));
}

// Getters
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

GuiManager* const RenderEngine::GetGuiManager() const noexcept {
  return this->guiManager_;
}

const Vector2<float> RenderEngine::GetTextSize(
    const std::string& text, const float& scale) const noexcept {
  return this->textHandler_->GetTextSize(text, scale);
}
