#include "mainAction.hpp"

// Base Class
void MainAction::InternalStart(Engine* const engine) const noexcept {
  engine->CompileComputeShader("CalulateDistances.comp", "CalulateDistances");
  engine->AddScene("default", new Scene())
      ->AddButton(new Button(Vector<float>(800, 450), "Button",
                             [](const Engine* const engine) {
                               std::cout << "BUTTON::Invoked" << std::endl;
                             }))
      ->AddTextRenderData(
          new TextRenderData("hello world", Vector<int>(10.0f, 450.0f),
                             Vector3<float>(1.0f, 1.0f, 1.0f), 5));
}

void MainAction::InternalUpdate(Engine* const engine) const noexcept {}

MainAction::MainAction() : Action() {}

MainAction::~MainAction() {}
