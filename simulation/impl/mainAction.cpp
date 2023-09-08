#include "mainAction.hpp"

// Base Class
void MainAction::InternalStart(Engine* const engine) const noexcept {
  engine->CompileComputeShader("CalulateDistances.comp", "CalulateDistances");

  engine->GetGuiManager()->AddWindow(new GuiWindow(
      "Test Window", []() { ImGui::Text("This is some useful text."); }));

  engine->AddScene("map", new Scene())
      ->AddButton(new Button(
          Vector2<float>(150, 850), Vector2<float>(120, 30),
          [](Engine* const engine, Button* const self) {
            engine->SetCurrentScene("edit");
          },
          "Edit Drone", engine))
      ->AddButton(new Button(
          Vector2<float>(800, 450), Vector2<float>(128, 128),
          [](Engine* const engine, Button* const self) {
            std::cout << "Hi" << std::endl;
          },
          new Texture("face.png")))
      ->AddMeshRenderData(new MeshRenderData(
          "Cone", (new Material())->RandomizeColor(),
          new Transform(Vector2<float>(800, 450), Vector2<float>(10, 10))));

  const Scene* const editScene =
      engine->AddScene("edit", new Scene())
          ->AddButton(new Button(
              Vector2<float>(75, 850), Vector2<float>(60, 30),
              [](Engine* const engine, Button* const self) {
                engine->SetCurrentScene("map");
              },
              "Back", engine))
          ->AddTextRenderData(
              new TextRenderData("Cost: 10", Vector2<int>(25, 775)))
          ->AddTextRenderData(
              new TextRenderData("Power Remaining: 0", Vector2<int>(25, 745)));

  const int grid[] = {
      0, 1, 1, 1, 0,  //
      0, 1, 1, 1, 0,  //
      0, 1, 1, 1, 0,  //
      0, 1, 1, 1, 0,  //
      0, 0, 1, 0, 0,  //
  };
  for (unsigned int y = 0, i = 0; y < 5; y++) {
    for (unsigned int x = 0; x < 5; x++) {
      if (grid[y * 5 + x] == 1) {
        editScene->AddButton(
            (new Button(Vector2<float>(x * 105, y * 105 + 200),
                        Vector2<float>(50, 50),
                        [](Engine* const engine, Button* const self) {
                          int ID = *reinterpret_cast<int*>(self->GetMetaData());
                          std::cout << ID << std::endl;
                        }))
                ->SetMetaData(reinterpret_cast<void*>(new int(i)),
                              [](void* const metaData_) {
                                delete reinterpret_cast<int*>(metaData_);
                              }));
        i++;
      }
    }
  }
}

void MainAction::InternalUpdate(Engine* const engine) const noexcept {}

void MainAction::InternalFinish(Engine* const engine) const noexcept {}

MainAction::MainAction() : Action() {}

MainAction::~MainAction() {}
