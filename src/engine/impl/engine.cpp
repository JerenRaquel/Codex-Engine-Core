#include "../headers/engine.hpp"

void Engine::MoveCamera() noexcept {
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

Engine::Engine(const Vector<int>& windowSize, const std::string& name) {
  this->windowSize_ = windowSize;
  this->renderer_ = new RenderEngine(windowSize, name);
  this->camera_ = new Camera(windowSize, 0.1f, 100.0f);
  this->droneManager_ = new DroneManager();
}

Engine::~Engine() {
  delete this->droneManager_;
  delete this->renderer_;
  delete this->camera_;
}

void Engine::Start() {
  // Initilize simulation stuff
  this->renderer_->CompileShader("vertex.glsl", "fragment.glsl", "default");
  this->droneManager_->OnStart(this);

  // Main loop
  while (!glfwWindowShouldClose(this->renderer_->GetWindow())) {
    this->MoveCamera();
    this->camera_->Recalculate();

    this->droneManager_->OnUpdate(this);

    this->renderer_->Draw(this->camera_);

    // update other events like input handling
    glfwPollEvents();
  }
}

Drone* Engine::AddDrone(Drone* drone) const noexcept {
  return this->AddDrone(drone, "generic");
}

Drone* Engine::AddDrone(Drone* drone, const std::string& tag) const noexcept {
  this->droneManager_->AddDrone(drone, tag);
  this->renderer_->AddMesh(drone->GetMesh());
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
