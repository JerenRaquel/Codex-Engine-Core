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
          Vector<float> dronePosition = self->GetMesh()->GetPosition();

          // Fly towards center
          if (dronePosition.x < 700.0f || dronePosition.x > 800.0f ||
              dronePosition.y < 400.0f || dronePosition.y > 500.0f) {
            Vector<float> towardsCenter =
                Vector<float>(800.0f, 450.0f) - self->GetMesh()->GetPosition();
            float towardsCenterAngle = towardsCenter.ToDegreeAngle();
            float turningAngle =
                towardsCenterAngle - self->GetMesh()->GetRotation();

            if (turningAngle > 180.0f) {
              turningAngle -= 360.0f;
            } else if (turningAngle < -180.0f) {
              turningAngle += 360.0f;
            }

            self->GetMesh()->Rotate(turningAngle * 0.05f);
          }

          std::vector<Drone*>* const drones = droneManager->GetAllDrones();

          // Fly with other drones
          float sum = 0.0f;
          unsigned int amount = 0;
          for (auto* drone : *drones) {
            Vector<float> position = drone->GetMesh()->GetPosition();
            Vector<float> selfPosition = self->GetMesh()->GetPosition();
            if (position == selfPosition) {
              continue;
            }

            float distance = selfPosition.Distance(position);

            if (distance < 20.0f) {
              Vector3<float> color =
                  drone->GetMesh()->GetColor() - self->GetMesh()->GetColor();
              float bias = color.x + color.y + color.z;
              bias /= 3.0f;

              sum += drone->GetMesh()->GetRotation() * (1.0f - bias);
              amount++;
            }
          }
          if (amount > 0) {
            float average = sum / amount;
            float newRotation = average + self->GetMesh()->GetRotation();
            newRotation /= 2.0f + 90.0f + (std::rand() % 30 - 15.0f);
            newRotation -= self->GetMesh()->GetRotation();
            newRotation *= 0.05f;
            self->GetMesh()->Rotate(newRotation);
          }

          // Avoid other drones
          for (auto* drone : *drones) {
            Vector<float> position = drone->GetMesh()->GetPosition();
            Vector<float> selfPosition = self->GetMesh()->GetPosition();
            if (position == selfPosition) {
              continue;
            }

            float distance = selfPosition.Distance(position);

            if (distance <= 20.0f) {
              Vector<float> awayFromDrone = selfPosition - position;
              float awayFromDroneAngle = awayFromDrone.ToDegreeAngle();
              float turningAngle =
                  awayFromDroneAngle - self->GetMesh()->GetRotation();

              if (turningAngle > 180.0f) {
                turningAngle -= 360.0f;
              } else if (turningAngle < -180.0f) {
                turningAngle += 360.0f;
              }

              self->GetMesh()->Rotate(turningAngle * 0.05f);
            }
          }

          // Fly forwards
          self->GetMesh()->Translate(self->GetMesh()->GetDirectionVector(),
                                     5.0f);

          // Bounds
          Vector<float> position = self->GetMesh()->GetPosition();
          if (position.x > 1600) {
            self->GetMesh()->SetPosition(Vector<float>(0, position.y));
            self->GetMesh()->SetRotation(90.0f);
          } else if (position.x < 0) {
            self->GetMesh()->SetPosition(Vector<float>(1600, position.y));
            self->GetMesh()->SetRotation(270.0f);
          }

          if (position.y > 900) {
            self->GetMesh()->SetPosition(Vector<float>(position.x, 0));
            self->GetMesh()->SetRotation(0.0f);
          } else if (position.y < 0) {
            self->GetMesh()->SetPosition(Vector<float>(position.x, 900));
            self->GetMesh()->SetRotation(180.0f);
          }

          // Drones that flock together have similar colors
          Vector3<float> colorSum;
          float colorAmount = 0.0f;
          for (auto* drone : *drones) {
            Vector<float> position = drone->GetMesh()->GetPosition();
            Vector<float> selfPosition = self->GetMesh()->GetPosition();
            if (position == selfPosition) {
              continue;
            }

            float distance = selfPosition.Distance(position);
            float selfRotation = self->GetMesh()->GetRotation();
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
