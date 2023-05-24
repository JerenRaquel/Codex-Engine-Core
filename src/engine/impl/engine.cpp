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

void Engine::OnStart() noexcept {
  this->renderer_->CompileShader("vertex.glsl", "fragment.glsl", "default");
  for (unsigned int i = 0; i < this->startFunctions_->size(); i++) {
    this->startFunctions_->at(i)(this);
  }
}

void Engine::OnUpdate() noexcept {
  this->MoveCamera();
  for (unsigned int i = 0; i < this->updateFunctions_->size(); i++) {
    this->updateFunctions_->at(i)(this);
  }
}

Engine::Engine(const Vector<int>& windowSize, const std::string& name) {
  this->windowSize_ = windowSize;
  this->renderer_ = new RenderEngine(windowSize, name);
  this->camera_ = new Camera(windowSize, 0.1f, 100.0f);
  this->startFunctions_ = new std::vector<void (*)(Engine* const engine)>();
  this->updateFunctions_ = new std::vector<void (*)(Engine* const engine)>();
  this->drones_ = new std::vector<Drone*>();
}

Engine::~Engine() {
  for (unsigned int i = 0; i < this->drones_->size(); i++) {
    delete this->drones_->at(i);
  }
  delete this->drones_;

  delete this->renderer_;
  delete this->camera_;
  delete this->startFunctions_;
  delete this->updateFunctions_;
}

void Engine::Start() {
  this->OnStart();
  while (!glfwWindowShouldClose(this->renderer_->GetWindow())) {
    this->OnUpdate();
    this->camera_->Recalculate();

    this->renderer_->Draw(this->camera_);

    // update other events like input handling
    glfwPollEvents();
  }
}

void Engine::AddStartFunction(void (*func)(Engine* const engine)) noexcept {
  this->startFunctions_->push_back(func);
}

void Engine::AddUpdateFunction(void (*func)(Engine* const engine)) noexcept {
  this->updateFunctions_->push_back(func);
}

Drone* Engine::AddDrone(Drone* drone) noexcept {
  this->drones_->push_back(drone);
  this->renderer_->AddMesh(drone->GetMesh());
  return drone;
}

// Getters
RenderEngine* const Engine::GetRenderer() const noexcept {
  return this->renderer_;
}

Vector<int> Engine::GetWindowSize() const noexcept { return this->windowSize_; }

std::vector<Drone*>* const Engine::GetDrones() const noexcept {
  return this->drones_;
}
