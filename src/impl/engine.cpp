#include "../headers/engine.hpp"

Engine::Engine(const Vector<int>& windowSize, const std::string& name) {
  this->windowSize_ = windowSize;
  this->renderer_ = new RenderEngine(windowSize, name);
}

Engine::~Engine() {}

void Engine::Start() {
  this->renderer_->CompileShader("vertex.glsl", "fragment.glsl", "default");

  this->renderer_
      ->AddQuad(new Quad(Vector<float>(5, 5), Vector<float>(2.5, 2.5)))
      ->SetScale(Vector<float>(10.0f, 10.0f))
      ->SetPosition(
          Vector<float>(this->windowSize_.x / 2.0f, this->windowSize_.y / 2.0f))
      ->SetColor(1.0f, 0.0f, 0.0f);

  this->renderer_->Start();
}
