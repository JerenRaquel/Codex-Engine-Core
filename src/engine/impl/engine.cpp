#include "../headers/engine.hpp"

#include "../../../tools/tracy/tracy/Tracy.hpp"

void Engine::MoveCamera() noexcept {
  if (glfwGetKey(this->renderer_->GetWindow(), GLFW_KEY_R) == GLFW_PRESS) {
    this->camera_->ResetPosition();
    return;
  }

  Vector<float> direction;
  if (glfwGetKey(this->renderer_->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
    direction.y = -1.0f;
  } else if (glfwGetKey(this->renderer_->GetWindow(), GLFW_KEY_S) ==
             GLFW_PRESS) {
    direction.y = 1.0f;
  }

  if (glfwGetKey(this->renderer_->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
    direction.x = 1.0f;
  } else if (glfwGetKey(this->renderer_->GetWindow(), GLFW_KEY_D) ==
             GLFW_PRESS) {
    direction.x = -1.0f;
  }
  if (direction.x != 0.0f && direction.y != 0.0f) {
    direction.x *= 0.70710678118f;  // sqrt(2)/2
    direction.y *= 0.70710678118f;
  }
  this->camera_->UpdatePosition(direction);
}

void Engine::CalculateMousePosition() noexcept {
  double xpos, ypos;
  glfwGetCursorPos(this->renderer_->GetWindow(), &xpos, &ypos);

  this->mousePosition_ = Vector<float>(xpos, ypos);
  if (glfwGetMouseButton(this->GetRenderer()->GetWindow(),
                         GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    this->isMouseDown_ = true;
  } else {
    this->isMouseDown_ = false;
  }
}

void Engine::CreatePrimativeMeshes() const noexcept {
  float coneVertices[] = {
      0.0f,  2.5f,  0.0f,  // top center
      -2.5f, -2.5f, 0.0f,  // bottom left
      2.5f,  -2.5f, 0.0f,  // bottom right
  };
  unsigned int coneIndices[] = {
      0, 1, 2,  // first triangle
  };

  Mesh* coneMesh = new Mesh(coneVertices, 9, coneIndices, 3);
  this->renderer_->AddMeshType("Cone", coneMesh);

  float quadVertices[] = {
      -1.0f, 1.0f,  0.0f,  // top left
      -1.0f, -1.0f, 0.0f,  // bottom left
      1.0f,  -1.0f, 0.0f,  // bottom right
      1.0f,  1.0f,  0.0f,  // top right
  };
  unsigned int quadIndices[] = {
      0, 1, 2,  // first triangle
      0, 2, 3,  // second triangle
  };

  Mesh* quadMesh = new Mesh(quadVertices, 12, quadIndices, 6);
  this->renderer_->AddMeshType("Quad", quadMesh);
}

Engine::Engine(const Vector<int>& windowSize, const std::string& name,
               const std::vector<std::string>& args) {
  this->windowSize_ = windowSize;
  this->args_ = new std::vector<std::string>(args);
  this->renderer_ =
      new RenderEngine(windowSize, name, "BasicCrayon-Regular.ttf", "Crayon");
  this->computeShaderCompiler_ = new ComputeShaderCompiler();
  this->camera_ = new Camera(windowSize, 0.1f, 100.0f);
  this->actions_ = new std::vector<Action*>();
  this->computeShaders_ = new std::map<std::string, ComputeShader*>();
  this->computeShaderBuffers_ =
      new std::map<std::string, ComputeShaderBuffer*>();
  // TEMP - start
  this->renderData_ = new std::vector<RenderData*>();
  this->buttons_ = new std::vector<Button*>();
  // TEMP - end
}

Engine::~Engine() {
  delete this->renderer_;
  delete this->computeShaderCompiler_;
  delete this->camera_;

  for (Action* action : *this->actions_) {
    delete action;
  }
  delete this->actions_;

  delete this->computeShaders_;
  for (auto& computeShaderBuffer : *this->computeShaderBuffers_) {
    delete computeShaderBuffer.second;
  }
  delete this->computeShaderBuffers_;

  // TEMP - start
  for (auto renderData : *this->renderData_) {
    delete renderData;
  }
  delete this->renderData_;

  for (auto button : *this->buttons_) {
    delete button;
  }
  delete this->buttons_;
  // TEMP - end
}

// Utility
void Engine::Start() {
  // Initilize renderer stuff
  this->renderer_->CompileShader("vertex.vs", "fragment.fs", "default");
  this->renderer_->CompileShader("button.vs", "button.fs", "button");
  this->renderer_->CompileShader("text.vs", "text.fs", "Crayon");
  this->CreatePrimativeMeshes();

  // TEMP - start
  this->renderer_->SetRenderDataPointer(this->renderData_);
  // TEMP - end

  // Initilize actions
  for (unsigned int i = 0; i < this->actions_->size(); i++) {
    this->actions_->at(i)->OnStart(this);
  }

  // Main loop
  while (!glfwWindowShouldClose(this->renderer_->GetWindow())) {
    FrameMark;
    this->MoveCamera();
    glm::mat4x4* orthoViewMatrixCached = this->camera_->GetViewOrthoMatrix();
    this->CalculateMousePosition();

    // Update actions
    for (unsigned int i = 0; i < this->actions_->size(); i++) {
      this->actions_->at(i)->OnUpdate(this);
    }

    // TEMP - start
    for (unsigned int i = 0; i < this->buttons_->size(); i++) {
      Button* button = this->buttons_->at(i);
      if (button->IsHovered(this->mousePosition_) && this->isMouseDown_) {
        button->InvokeCallback();
        this->isMouseDown_ = false;
        break;
      }
    }
    // TEMP - end

    this->renderer_->Render(orthoViewMatrixCached);

    // update other events like input handling
    glfwPollEvents();
  }
}

void Engine::CompileComputeShader(const std::string& computeFile,
                                  const std::string& name) const {
  if (this->computeShaders_->count(name) > 0) {
    throw std::runtime_error("Compute shader already exists");
  }

  ComputeShader* computeShader =
      new ComputeShader(this->computeShaderCompiler_, computeFile);
  this->computeShaders_->insert(
      std::pair<std::string, ComputeShader*>(name, computeShader));
}

ComputeShaderBuffer* const Engine::AssignNewComputeShaderBuffer(
    const std::string& name, const unsigned int& width,
    const unsigned int& height) const {
  if (this->computeShaderBuffers_->count(name) > 0) {
    throw std::runtime_error("Compute shader buffer already exists");
  }
  ComputeShaderBuffer* buffer = new ComputeShaderBuffer(width, height);
  this->computeShaderBuffers_->insert(
      std::pair<std::string, ComputeShaderBuffer*>(name, buffer));
  return buffer;
}

const Engine* const Engine::AddAction(Action* action) const noexcept {
  this->actions_->push_back(action);
  return this;
}

const Engine* const Engine::AddButton(Button* button) const noexcept {
  this->buttons_->push_back(button);
  RenderData* renderData = new RenderData();
  renderData->meshType = "Quad";
  renderData->material = button->GetMaterial();
  renderData->transform = button->GetTransform();
  this->renderData_->push_back(renderData);
  return this;
}

// Getters
RenderEngine* const Engine::GetRenderer() const noexcept {
  return this->renderer_;
}

Vector<int> Engine::GetWindowSize() const noexcept { return this->windowSize_; }

std::vector<std::string>* const Engine::GetArgs() const noexcept {
  return this->args_;
}

Vector<float> Engine::GetMousePosition() const noexcept {
  return this->mousePosition_;
}

ComputeShader* const Engine::GetComputeShader(const std::string& name) const {
  if (this->computeShaders_->count(name) == 0) {
    throw std::runtime_error("Compute shader does not exist");
  }
  return this->computeShaders_->at(name);
}

ComputeShaderBuffer* const Engine::GetComputeShaderBuffer(
    const std::string& name) const noexcept {
  if (this->computeShaderBuffers_->count(name) == 0) {
    return nullptr;
  }

  return this->computeShaderBuffers_->at(name);
}
