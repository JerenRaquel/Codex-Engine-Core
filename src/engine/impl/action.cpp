#include "action.hpp"

Action::Action() {}

Action::~Action() {}

void Action::OnStart(const Engine* const engine) const noexcept {
  this->InternalStart(engine);
}

void Action::OnUpdate(const Engine* const engine) const noexcept {
  this->InternalUpdate(engine);
}
