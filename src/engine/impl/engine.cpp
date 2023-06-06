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

  int windowX, windowY;
  glfwGetWindowPos(this->renderer_->GetWindow(), &windowX, &windowY);

  this->mousePosition_ = Vector<int>(xpos - windowX, ypos - windowY);
}

Engine::Engine(const Vector<int>& windowSize, const std::string& name) {
  this->windowSize_ = windowSize;
  this->renderer_ =
      new RenderEngine(windowSize, name, "BasicCrayon-Regular.ttf", "Crayon");
  this->computeShaderCompiler_ = new ComputeShaderCompiler();
  this->camera_ = new Camera(windowSize, 0.1f, 100.0f);
  this->droneManager_ = new DroneManager(this);
  this->meshes_ = new std::vector<Mesh*>();
  this->computeShaders_ = new std::map<std::string, ComputeShader*>();
  this->computeShaderBuffers_ =
      new std::map<std::string, ComputeShaderBuffer*>();
}

Engine::~Engine() {
  delete this->droneManager_;
  delete this->renderer_;
  delete this->computeShaderCompiler_;
  delete this->camera_;

  for (unsigned int i = 0; i < this->meshes_->size(); i++) {
    delete this->meshes_->at(i);
  }
  delete this->meshes_;

  delete this->computeShaders_;
  for (auto& computeShaderBuffer : *this->computeShaderBuffers_) {
    delete computeShaderBuffer.second;
  }
  delete this->computeShaderBuffers_;
}

// Utility
void Engine::Start() {
  // Initilize renderer stuff
  this->renderer_->CompileShader("vertex.vs", "fragment.fs", "default");
  this->renderer_->CompileShader("text.vs", "text.fs", "Crayon");

  // Initilize simulation stuff
  this->renderer_->SetMeshPointer(this->meshes_);  // TEMP
  this->droneManager_->OnStart();

  // Main loop
  while (!glfwWindowShouldClose(this->renderer_->GetWindow())) {
    FrameMark;
    this->MoveCamera();
    glm::mat4x4* orthoViewMatrixCached = this->camera_->GetViewOrthoMatrix();
    this->CalculateMousePosition();

    this->droneManager_->OnUpdate();

    // TEMP
    this->renderer_->DrawText("hello world", Vector<int>(10.0f, 450.0f), 1);

    this->renderer_->Render(orthoViewMatrixCached);

    // update other events like input handling
    glfwPollEvents();
  }
}

void Engine::CompileComputeShader(const std::string& computeFile,
                                  const std::string& name) {
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

Drone* Engine::AddDrone(Drone* drone) const noexcept {
  return this->AddDrone(drone, "generic");
}

Drone* Engine::AddDrone(Drone* drone, const std::string& tag) const noexcept {
  this->droneManager_->AddDrone(drone, tag);
  this->meshes_->push_back(drone->GetMesh());
  return drone;
}

// Getters
RenderEngine* const Engine::GetRenderer() const noexcept {
  return this->renderer_;
}

Vector<int> Engine::GetWindowSize() const noexcept { return this->windowSize_; }

DroneManager* const Engine::GetDroneManager() const noexcept {
  return this->droneManager_;
}

Vector<int> Engine::GetMousePosition() const noexcept {
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
