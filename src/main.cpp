/*	Jeren Raquel
 *	==Drone Simulation==
 *	Description
 */
#include "engine/headers/engine.hpp"

int main(int argc, char** argv) {
  Vector<int> size(1600, 900);

  Engine* engine = new Engine(size, "Drone Simulation");
  engine->AddStartFunction([](Engine* const engine) {
    Vector<int> center = engine->GetWindowSize() / 2;
    engine
        ->AddDrone(new Drone(Vector<float>(center.x, center.y),
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
