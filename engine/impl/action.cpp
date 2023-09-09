#include "action.hpp"

Action::Action() {}

Action::~Action() {}

void Action::OnStart(Engine* const engine) const noexcept {
  this->InternalStart(engine);
}

void Action::OnUpdate(Engine* const engine) const noexcept {
  this->InternalUpdate(engine);
}

void Action::OnFinish(Engine* const engine) const noexcept {
  this->InternalFinish(engine);
}
