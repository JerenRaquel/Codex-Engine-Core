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

  for (unsigned int i = 0; i < 10; i++) {
    Vector<float> position(std::rand() % engine->GetWindowSize().x,
                           std::rand() % engine->GetWindowSize().y);

    engine
        ->AddDrone(new Drone(position, Vector<float>(10.0f, 10.0f),
                             Vector3<float>(1.0f, 0.0f, 0.0f)),
                   i < 5 ? "red" : "blue")
        ->AssignStartFunction([](Engine* const engine, Drone* const self,
                                 const std::string& tag,
                                 const unsigned int id) {
          if (tag == "red") {
            self->GetMesh()->SetColor(Vector3<float>(1.0f, 0.0f, 0.0f));
          } else {
            self->GetMesh()->SetColor(Vector3<float>(0.0f, 0.0f, 1.0f));
          }
        })
        ->AssignUpdateFunction(
            [](Engine* const engine, Drone* const self, const std::string& tag,
               const unsigned int id) { self->GetMesh()->Rotate(1.0f); })
        ->GetMesh()
        ->SetRotation(std::rand() % 360);
  }

  engine->Start();
  delete engine;

  return 0;
}
