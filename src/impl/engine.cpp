#include "../headers/engine.hpp"

Engine::Engine(const Vector<int>& windowSize, const std::string& name) {
  this->renderer_ = new RenderEngine(windowSize, name);
}

Engine::~Engine() {}

void Engine::Start() {
  this->renderer_->AddQuad(
      new Quad(Vector<float>(5, 5), Vector<float>(2.5, 2.5)));
  this->renderer_->CompileShader("vertex.glsl", "fragment.glsl", "default");
  float color[4] = {0.0f, 1.0f, 0.0f, 1.0f};
  this->renderer_->GetShader("default")->AddUniformDataID("color", color, 4);
  this->renderer_->GetShader("default")->AddUniformDataID(
      "projection", this->renderer_->GetCamera()->GetOrthoMatrix(), 16);
  this->renderer_->GetShader("default")->AddUniformDataID(
      "view", this->renderer_->GetCamera()->GetViewMatrix(), 16);
  this->renderer_->Start();
}
