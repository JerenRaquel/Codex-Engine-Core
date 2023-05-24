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
  unsigned int droneCount = 10000;

  Engine* engine = new Engine(size, "Drone Simulation");

  for (unsigned int i = 0; i < droneCount; i++) {
    Vector<float> position(std::rand() % engine->GetWindowSize().x,
                           std::rand() % engine->GetWindowSize().y);

    engine->AddDrone(new Drone(position, Vector<float>(1.5f, 1.5f)))
        ->OnStart([](DroneManager* const droneManager, Drone* const self,
                     const std::string& tag, const unsigned int id) {
          float r = static_cast<float>(std::rand() % 255) / 255.0f;
          float g = static_cast<float>(std::rand() % 255) / 255.0f;
          float b = static_cast<float>(std::rand() % 255) / 255.0f;
          self->GetMesh()->SetColor(Vector3<float>(r, g, b));
        })
        ->OnUpdate([](DroneManager* const droneManager, Drone* const self,
                      const std::string& tag, const unsigned int id) {
          if (id < droneManager->GetAllDroneCount() / 2) {
            self->GetMesh()->Rotate(1.0f);
          } else {
            self->GetMesh()->Rotate(-1.0f);
          }
        })
        ->GetMesh()
        ->SetRotation(std::rand() % 360);
  }

  engine->Start();
  delete engine;

  return 0;
}
