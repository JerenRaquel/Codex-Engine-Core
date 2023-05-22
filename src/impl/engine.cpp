#include "../headers/engine.hpp"

Engine::Engine(const Vector<int>& windowSize, const std::string& name) {
  this->renderer_ = new RenderEngine(windowSize, name);
}

Engine::~Engine() {}

void Engine::Start() {
  this->renderer_->AddQuad(
      new Quad(Vector<float>(5, 5), Vector<float>(-5, -5)));
  this->renderer_->Start();
}
