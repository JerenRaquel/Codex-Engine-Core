#include "testAction.hpp"

// Base Class
void TestAction::InternalStart(const Engine* const engine) const noexcept {
  engine->CompileComputeShader("CalulateDistances.comp", "CalulateDistances");
  engine->AddButton(new Button(
      Vector<float>(800, 450),
      []() { std::cout << "BUTTON::Invoked" << std::endl; },
      Vector<float>(100, 100)));
}

void TestAction::InternalUpdate(const Engine* const engine) const noexcept {
  engine->GetRenderer()->DrawText("hello world", Vector<int>(10.0f, 450.0f), 1);
}

TestAction::TestAction() : Action() {}

TestAction::~TestAction() {}
