#include "action.hpp"

Action::Action() {}

Action::~Action() {}

void Action::OnStart(Engine* const engine) noexcept {
  this->InternalStart(engine);
}

void Action::OnUpdate(Engine* const engine) noexcept {
  this->InternalUpdate(engine);
}

void Action::OnFinish(Engine* const engine) noexcept {
  this->InternalFinish(engine);
}
