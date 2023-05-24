/*	Jeren Raquel
 *	==Project Name==
 *	Description
 */
//* Custom
#include "engine/headers/engine.hpp"

int main(int argc, char** argv) {
  Vector<int> size(900, 640);

  Engine* engine = new Engine(size, "Hello World");
  engine->AddStartFunction([](Engine* const engine) {
    engine
        ->AddDrone(new Drone(Vector<float>(450.0f, 320.0f),
                             Vector<float>(10.0f, 10.0f),
                             Vector3<float>(1.0f, 0.0f, 0.0f)))
        ->GetMesh()
        ->SetRotation(45.0f);
  });
  engine->AddUpdateFunction([](Engine* const engine) {
    for (auto drone : *engine->GetDrones()) {
      drone->GetMesh()->Rotate(1.0f);
    }
  });

  engine->Start();
  delete engine;

  return 0;
}
