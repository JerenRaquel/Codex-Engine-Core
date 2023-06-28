#include "mainAction.hpp"

// Base Class
void MainAction::InternalStart(Engine* const engine) const noexcept {
  engine->CompileComputeShader("CalulateDistances.comp", "CalulateDistances");

  engine->AddScene("map", new Scene())
      ->AddButton(new Button(
          Vector<float>(150, 850), Vector<float>(120, 30),
          [](Engine* const engine, Button* const self) {
            engine->SetCurrentScene("edit");
          },
          "Edit Drone", engine))
      ->AddButton(new Button(
          Vector<float>(800, 450), Vector<float>(128, 128),
          [](Engine* const engine, Button* const self) {
            std::cout << "Hi" << std::endl;
          },
          new Texture("face.png")))
      ->AddMeshRenderData(new MeshRenderData(
          "Cone", (new Material())->RandomizeColor(),
          new Transform(Vector<float>(800, 450), Vector<float>(10, 10))));

  const Scene* const editScene =
      engine->AddScene("edit", new Scene())
          ->AddButton(new Button(
              Vector<float>(75, 850), Vector<float>(60, 30),
              [](Engine* const engine, Button* const self) {
                engine->SetCurrentScene("map");
              },
              "Back", engine))
          ->AddTextRenderData(
              new TextRenderData("Cost: 10", Vector<int>(25, 775),
                                 Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f))
          ->AddTextRenderData(
              new TextRenderData("Power Remaining: 0", Vector<int>(25, 745),
                                 Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f));

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
            (new Button(Vector<float>(x * 105, y * 105 + 200),
                        Vector<float>(50, 50),
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

MainAction::MainAction() : Action() {}

MainAction::~MainAction() {}
