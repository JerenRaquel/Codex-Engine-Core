/*	Jeren Raquel
 *	==Drone Simulation==
 *	Description
 */
// Std
#include <cstdlib>
#include <vector>
// Custom
#include "engine/headers/engine.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <drone count>" << std::endl;
    return 1;
  }

  Vector<int> size(1600, 900);
  Vector<float> scale(2.5f, 2.5f);
  unsigned int droneCount = std::atoi(argv[1]);

  Engine* engine = new Engine(size, "Drone Simulation");

  for (unsigned int i = 0; i < droneCount; i++) {
    Vector<float> position(std::rand() % engine->GetWindowSize().x,
                           std::rand() % engine->GetWindowSize().y);

    engine->AddDrone(new Drone(position, scale))
        ->OnStart([](Engine* const engine, Drone* const self,
                     const std::string& tag, const unsigned int id) {
          if (id < 10) {
            self->GetMesh()->SetScale(Vector<float>(5.0f, 5.0f));
          }
          float r = static_cast<float>(std::rand() % 255) / 255.0f;
          float g = static_cast<float>(std::rand() % 255) / 255.0f;
          float b = static_cast<float>(std::rand() % 255) / 255.0f;
          self->GetMesh()
              ->SetColor(Vector3<float>(r, g, b))
              ->SetRotation(std::rand() % 360);
        })
        ->OnUpdate([](Engine* const engine, Drone* const self,
                      const std::string& tag, const unsigned int id) {
          Vector<float> selfPosition = self->GetMesh()->GetPosition();
          float selfRotation = self->GetMesh()->GetRotation();
          Vector<float> center(800.0f, 450.0f);
          float targetBias = 0.05f;
          float cohesionBias = 0.02f;
          float separationBias = 0.01f;

          std::vector<Drone*>* const allDrones =
              engine->GetDroneManager()->GetAllDrones();
          std::vector<Drone*>* const drones100 =
              engine->GetDroneManager()->FilterBasedOnRange(
                  allDrones, selfPosition, 100.0f);
          std::vector<Drone*>* const drones20 =
              engine->GetDroneManager()->FilterBasedOnRange(
                  drones100, selfPosition, 20.0f);

          // Fly towards center
          Vector<float> towardsCenter = center - selfPosition;
          self->GetMesh()->RotateTowards(towardsCenter, targetBias);

          // Fly with other drones
          if (drones20->size() > 0) {
            float sum = 0.0f;
            for (auto* drone : *drones20) {
              // Avoid other drones
              self->GetMesh()->RotateTowards(
                  selfPosition - drone->GetMesh()->GetPosition(),
                  separationBias);

              // Begin aggregation for cohesion
              float bias = self->GetMesh()->GetColor().DifferenceBias(
                  drone->GetMesh()->GetColor());
              sum += drone->GetMesh()->GetRotation() * (1.0f - bias);
            }
            float average = sum / drones20->size();
            float newRotation = average + selfRotation;
            newRotation /= 77.0f + (std::rand() % 30);
            newRotation -= selfRotation;
            newRotation *= cohesionBias;
            self->GetMesh()->Rotate(newRotation);
          }

          // Fly forwards
          self->GetMesh()->Translate(self->GetMesh()->GetDirectionVector(),
                                     5.0f);

          // Bounds
          selfPosition = self->GetMesh()->GetPosition();
          if (selfPosition.x > 1600) {
            selfPosition.x = 0.0f;
            selfPosition.y = std::rand() % 900;
            self->GetMesh()->SetPosition(selfPosition);
          } else if (selfPosition.x < 0) {
            selfPosition.x = 1600.0f;
            selfPosition.y = std::rand() % 900;
            self->GetMesh()->SetPosition(selfPosition);
          }
          if (selfPosition.y > 900) {
            selfPosition.y = 0.0f;
            selfPosition.x = std::rand() % 1600;
            self->GetMesh()->SetPosition(selfPosition);
          } else if (selfPosition.y < 0) {
            selfPosition.y = 900.0f;
            selfPosition.x = std::rand() % 1600;
            self->GetMesh()->SetPosition(selfPosition);
          }

          // Drones that flock together have similar colors
          if (id >= 10 && drones100->size() > 0) {
            Vector3<float> colorSum;
            float colorAmount = 0.0f;
            for (auto* drone : *drones100) {
              float droneRotation = drone->GetMesh()->GetRotation();
              if (selfRotation < droneRotation + 5.0f &&
                  selfRotation > droneRotation - 5.0f) {
                colorSum += drone->GetMesh()->GetColor();
                colorAmount++;
              }
            }
            if (colorAmount > 0) {
              Vector3<float> newColor = colorSum / colorAmount;
              self->GetMesh()->SetColor(
                  self->GetMesh()->GetColor().Lerp(newColor, 0.5f));
            }
          }

          delete drones100;
          delete drones20;
        });
  }

  engine->Start();
  delete engine;

  return 0;
}
