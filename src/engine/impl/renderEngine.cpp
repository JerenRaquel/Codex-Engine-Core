#include "../headers/renderEngine.hpp"

#include "../../../tools/tracy/tracy/Tracy.hpp"

void RenderEngine::InitOpenGL(const Vector<int>& size,
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
}

void RenderEngine::RenderMeshBatch(
    const glm::mat4x4* const orthoViewMatrix) const noexcept {
  ZoneScopedN("RenderEngine::RenderMeshBatch");
  //* Check if mesh pointer is valid
  if (this->renderDataPointer_ == nullptr) return;

  //* Draw Calls
  Shader* shader = nullptr;
  for (unsigned int i = 0; i < this->renderDataPointer_->size(); i++) {
    RenderData* data = this->renderDataPointer_->at(i);
    if (!data->material->ShouldRender()) continue;

    if (this->meshTypes_->count(data->meshType) == 0) continue;

    // Load Active Shader
    const std::string shaderName = data->material->GetShaderName();
    if (this->shaders_->count(shaderName) > 0) {
      shader = this->shaders_->at(shaderName);
    } else {
      shader = this->shaders_->at("default");
    }
    shader->Use();

    // Update Uniforms
    ZoneScopedN("RenderEngine::RenderMeshBatch::UpdateMVP");
    glm::mat4x4 mvp = *(orthoViewMatrix) * *(data->transform->GetModelMatrix());
    shader->PassUniformMatrix("mvp", &mvp);
    shader->PassUniform3f("color", data->material->GetColor());
    shader->PassUniform1f("alpha", data->material->GetAlpha());

    this->meshTypes_->at(data->meshType)->Draw();
  }
}

void RenderEngine::RenderTextBatch(
    const glm::mat4x4* const orthoMatrix) const noexcept {
  Shader* shader = this->shaders_->at(this->defaultTextShaderName_);
  shader->Use();
  shader->PassUniformMatrix("projection", this->textHandler_->GetOrthoMatrix());

  while (!this->textMetaData_->empty()) {
    TextMetaData data = this->textMetaData_->front();
    this->textMetaData_->pop();
    shader->PassUniform3f("textColor", data.color);
    this->textHandler_->DrawText(data.text, data.position, data.scale);
  }
}

RenderEngine::RenderEngine(const Vector<int>& size, const std::string& name,
                           const std::string& defaultFontFile,
                           const std::string& textShaderName)
    : defaultTextShaderName_(textShaderName) {
  // Setup OpenGL Window Context
  this->InitOpenGL(size, name);

  this->shaders_ = new std::map<std::string, Shader*>();
  this->shaderNames_ = new std::vector<std::string>();
  this->shaderCompiler_ = new ShaderCompiler();
  this->textHandler_ = new TextHandler(defaultFontFile, size);
  this->textMetaData_ = new std::queue<TextMetaData>();
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
  delete this->textMetaData_;
  for (auto mesh : *(this->meshTypes_)) {
    delete mesh.second;
  }
  delete this->meshTypes_;

  glfwTerminate();
}

void RenderEngine::Render(const glm::mat4x4* const orthoViewMatrix) {
  //* Clear Drawing Surface
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //* Render UI
  this->RenderTextBatch(orthoViewMatrix);

  //* Render Meshes
  this->RenderMeshBatch(orthoViewMatrix);

  //* Swap Buffers
  glfwSwapBuffers(this->window_);
}

void RenderEngine::DrawText(const std::string& text,
                            const Vector<int>& position,
                            const int& scale) const noexcept {
  this->DrawText(text, position, Vector3<float>(1.0f, 1.0f, 1.0f), scale);
}

void RenderEngine::DrawText(const std::string& text,
                            const Vector<int>& position,
                            const Vector3<float>& color,
                            const int& scale) const noexcept {
  TextMetaData data = {text, position, color, scale};
  this->textMetaData_->push(data);
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

// Setters
void RenderEngine::SetRenderDataPointer(
    std::vector<RenderData*>* const renderDataPointer) noexcept {
  this->renderDataPointer_ = renderDataPointer;
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
