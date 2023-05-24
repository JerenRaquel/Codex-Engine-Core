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
  Vector<int> size(1600, 900);
  Vector<float> scale(2.5f, 2.5f);
  unsigned int droneCount = 1000;

  Engine* engine = new Engine(size, "Drone Simulation");

  for (unsigned int i = 0; i < droneCount; i++) {
    Vector<float> position(std::rand() % engine->GetWindowSize().x,
                           std::rand() % engine->GetWindowSize().y);

    engine->AddDrone(new Drone(position, scale))
        ->OnStart([](DroneManager* const droneManager, Drone* const self,
                     const std::string& tag, const unsigned int id) {
          float r = static_cast<float>(std::rand() % 255) / 255.0f;
          float g = static_cast<float>(std::rand() % 255) / 255.0f;
          float b = static_cast<float>(std::rand() % 255) / 255.0f;
          self->GetMesh()
              ->SetColor(Vector3<float>(r, g, b))
              ->SetRotation(std::rand() % 360);
        })
        ->OnUpdate([](DroneManager* const droneManager, Drone* const self,
                      const std::string& tag, const unsigned int id) {
          std::vector<Drone*>* const drones = droneManager->GetAllDrones();
          Vector<float> selfPosition = self->GetMesh()->GetPosition();
          float selfRotation = self->GetMesh()->GetRotation();

          // Fly towards center
          if (selfPosition.x < 700.0f || selfPosition.x > 800.0f ||
              selfPosition.y < 400.0f || selfPosition.y > 500.0f) {
            Vector<float> towardsCenter =
                Vector<float>(800.0f, 450.0f) - selfPosition;
            self->GetMesh()->RotateTowards(towardsCenter, 0.05f);
          }

          // Fly with other drones
          float sum = 0.0f;
          unsigned int amount = 0;
          for (auto* drone : *drones) {
            float distance =
                selfPosition.Distance(drone->GetMesh()->GetPosition());
            if (distance == 0.0f) {
              continue;
            }

            if (distance <= 20.0f) {
              float bias = self->GetMesh()->GetColor().DifferenceBias(
                  drone->GetMesh()->GetColor());

              sum += drone->GetMesh()->GetRotation() * (1.0f - bias);
              amount++;
            }
          }
          if (amount > 0) {
            float average = sum / amount;
            float newRotation = average + selfRotation;
            newRotation /= 2.0f + 90.0f + (std::rand() % 30 - 15.0f);
            newRotation -= selfRotation;
            newRotation *= 0.05f;
            self->GetMesh()->Rotate(newRotation);
          }

          // Avoid other drones
          for (auto* drone : *drones) {
            float distance =
                selfPosition.Distance(drone->GetMesh()->GetPosition());
            if (distance == 0.0f) {
              continue;
            }

            if (distance <= 20.0f) {
              Vector<float> awayFromDrone =
                  selfPosition - drone->GetMesh()->GetPosition();
              self->GetMesh()->RotateTowards(awayFromDrone, 0.05f);
            }
          }

          // Fly forwards
          self->GetMesh()->Translate(self->GetMesh()->GetDirectionVector(),
                                     5.0f);

          // Bounds
          if (selfPosition.x > 1600) {
            self->GetMesh()->SetPosition(Vector<float>(0, selfPosition.y));
            self->GetMesh()->SetRotation(90.0f);
          } else if (selfPosition.x < 0) {
            self->GetMesh()->SetPosition(Vector<float>(1600, selfPosition.y));
            self->GetMesh()->SetRotation(270.0f);
          }

          if (selfPosition.y > 900) {
            self->GetMesh()->SetPosition(Vector<float>(selfPosition.x, 0));
            self->GetMesh()->SetRotation(0.0f);
          } else if (selfPosition.y < 0) {
            self->GetMesh()->SetPosition(Vector<float>(selfPosition.x, 900));
            self->GetMesh()->SetRotation(180.0f);
          }

          // Drones that flock together have similar colors
          Vector3<float> colorSum;
          float colorAmount = 0.0f;
          for (auto* drone : *drones) {
            float distance =
                selfPosition.Distance(drone->GetMesh()->GetPosition());
            if (distance == 0.0f) {
              continue;
            }

            float droneRotation = drone->GetMesh()->GetRotation();

            if (distance < 100.0f && selfRotation < droneRotation + 5.0f &&
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
        });
  }

  engine->Start();
  delete engine;

  return 0;
}
