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

  this->renderer_->AddQuad(new Quad(Vector<float>(5, 5)))
      ->SetScale(Vector<float>(10.0f, 10.0f))
      ->SetPosition(
          Vector<float>(this->windowSize_.x / 2.0f, this->windowSize_.y / 2.0f))
      ->SetColor(1.0f, 0.0f, 0.0f);
}

void Engine::OnUpdate() noexcept { this->MoveCamera(); }

Engine::Engine(const Vector<int>& windowSize, const std::string& name) {
  this->windowSize_ = windowSize;
  this->renderer_ = new RenderEngine(windowSize, name);
  this->camera_ = new Camera(windowSize, 0.1f, 100.0f);
}

Engine::~Engine() {}

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
