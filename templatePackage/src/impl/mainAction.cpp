#include "../headers/mainAction.hpp"

// Base Class
void MainAction::InternalStart(Engine* const engine) const noexcept {
  engine->CompileComputeShader("CalulateDistances.comp", "CalulateDistances");

  engine->GetGuiManager()->AddWindow(new GuiWindow(
      "Test Window", []() { ImGui::Text("This is some useful text."); }));

  engine->AddScene("main", new Scene())
      ->AddMeshRenderData(new MeshRenderData(
          "Cone", (new Material())->RandomizeColor(),
          new Transform(Vector2<float>(800, 450), Vector2<float>(10, 10))));
}

void MainAction::InternalUpdate(Engine* const engine) const noexcept {}

void MainAction::InternalFinish(Engine* const engine) const noexcept {}

MainAction::MainAction() : Action() {}

MainAction::~MainAction() {}
