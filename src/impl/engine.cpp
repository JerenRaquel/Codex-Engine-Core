#include "../headers/engine.hpp"

Engine::Engine(const Vector2& windowSize, const std::string& name) {
  this->renderer_ = new RenderEngine(windowSize, name);
}

Engine::~Engine() {}

void Engine::Start() { this->renderer_->Start(); }
