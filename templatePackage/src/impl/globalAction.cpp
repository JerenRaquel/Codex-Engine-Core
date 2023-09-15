#include "../headers/globalAction.hpp"

// Base Class
void GlobalAction::InternalStart(Engine* const engine) noexcept {
  engine->CompileComputeShader("CalulateDistances.comp", "CalulateDistances");

  engine->GetGuiManager()->AddWindow(new GuiWindow(
      "Test Window", []() { ImGui::Text("This is some useful text."); }));

  engine->AddScene("main", new Scene())
      ->AddMeshRenderData(new MeshRenderData(
          "Cone", (new Material())->RandomizeColor(),
          new Transform(Vector2<float>(800, 450), Vector2<float>(10, 10))));
}

void GlobalAction::InternalUpdate(Engine* const engine) noexcept {}

void GlobalAction::InternalFinish(Engine* const engine) noexcept {}

GlobalAction::GlobalAction() : Action() {}

GlobalAction::~GlobalAction() {}
