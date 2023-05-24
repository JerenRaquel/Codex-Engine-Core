/*	Jeren Raquel
 *	==Drone Simulation==
 *	Description
 */
// Std
#include <cstdlib>
// Custom
#include "engine/headers/engine.hpp"

int main(int argc, char** argv) {
  Vector<int> size(1600, 900);

  Engine* engine = new Engine(size, "Drone Simulation");
  engine->AddStartFunction([](Engine* const engine) {
    for (unsigned int i = 0; i < 10; i++) {
      Vector<float> position(std::rand() % engine->GetWindowSize().x,
                             std::rand() % engine->GetWindowSize().y);

      engine
          ->AddDrone(new Drone(position, Vector<float>(10.0f, 10.0f),
                               Vector3<float>(1.0f, 0.0f, 0.0f)))
          ->GetMesh()
          ->SetRotation(std::rand() % 360);
    }
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
