#include "mainAction.hpp"

// Base Class
void MainAction::InternalStart(Engine* const engine) const noexcept {
  engine->CompileComputeShader("CalulateDistances.comp", "CalulateDistances");
  engine->AddScene("map", new Scene())
      ->AddButton(new Button(
          Vector<float>(150, 850), Vector<float>(120, 30),
          [](Engine* const engine, const Button* const self) {
            engine->SetCurrentScene("edit");
          },
          "Edit Drone", engine));
  engine->AddScene("edit", new Scene())
      ->AddButton(new Button(
          Vector<float>(150, 850), Vector<float>(60, 30),
          [](Engine* const engine, const Button* const self) {
            engine->SetCurrentScene("map");
          },
          "Back", engine));
}

void MainAction::InternalUpdate(Engine* const engine) const noexcept {}

MainAction::MainAction() : Action() {}

MainAction::~MainAction() {}
