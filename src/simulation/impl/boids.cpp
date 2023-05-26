#include "../headers/boids.hpp"

#include "../../../tools/tracy/tracy/Tracy.hpp"

void Boids::InternalStart(Engine* const engine, const std::string& tag,
                          const unsigned int id) {
  float r = static_cast<float>(std::rand() % 255) / 255.0f;
  float g = static_cast<float>(std::rand() % 255) / 255.0f;
  float b = static_cast<float>(std::rand() % 255) / 255.0f;
  this->mesh_->SetColor(Vector3<float>(r, g, b))
      ->SetRotation(std::rand() % 360);
}

void Boids::InternalUpdate(Engine* const engine, const std::string& tag,
                           const unsigned int id) {
  Vector<float> selfPosition = this->mesh_->GetPosition();

  ZoneScopedN("Boids::DroneFetching");
  const auto alphas = engine->GetDroneManager()->GetDronesByTag("Alpha");
  const auto boids = engine->GetDroneManager()->GetDronesByTag("Boids");
  const auto closestAlpha =
      engine->GetDroneManager()->GetClosestDrone(alphas, selfPosition);
  const auto drones100 = engine->GetDroneManager()->FilterBasedOnRange(
      boids, selfPosition, 100.0f);
  const auto drones20 = engine->GetDroneManager()->FilterBasedOnRange(
      drones100, selfPosition, 20.0f);
  const auto alphas100 = engine->GetDroneManager()->FilterBasedOnRange(
      alphas, selfPosition, 100.0f);

  // Fly towards closest alpha
  Vector<float> towardsAlpha = closestAlpha->drone->GetMesh()->GetPosition() -
                               this->mesh_->GetPosition();
  this->mesh_->RotateTowards(towardsAlpha, this->targetBias);

  // Fly with other drones
  CohesionAndAvoidance(drones20);

  // Fly forwards
  Move();

  // Drones that flock together have similar colors
  BlendColors(drones100, id, 0.5f);
  BlendColors(alphas100, id, 0.5f);

  delete drones20;
  delete drones100;
  delete alphas100;
}

void Boids::CohesionAndAvoidance(
    const std::vector<DroneData*>* const drones) const noexcept {
  ZoneScopedN("Boids::CohesionAndAvoidance");
  if (drones->size() == 0) return;
  float sum = 0.0f;
  for (DroneData* droneData : *drones) {
    Mesh* droneMesh = droneData->drone->GetMesh();

    // Avoid other drones
    this->mesh_->RotateTowards(
        this->mesh_->GetPosition() - droneMesh->GetPosition(),
        this->separationBias);

    // Begin aggregation for cohesion
    float bias = this->mesh_->GetColor().DifferenceBias(droneMesh->GetColor());
    sum += droneMesh->GetRotation() * (1.0f - bias);
  }
  float average = sum / drones->size();
  float newRotation = average + this->mesh_->GetRotation();
  newRotation /= 77.0f + (std::rand() % 30);
  newRotation -= this->mesh_->GetRotation();
  newRotation *= this->cohesionBias;
  this->mesh_->Rotate(newRotation);
}

void Boids::Move() const noexcept {
  ZoneScopedN("Boids::Move");
  this->mesh_->Translate(this->mesh_->GetDirectionVector(), this->flySpeed);

  // Bounds
  Vector<float> selfPosition = this->mesh_->GetPosition();
  if (selfPosition.x > 1600) {
    selfPosition.x = 0.0f;
    // selfPosition.y = std::rand() % 900;
    this->mesh_->SetPosition(selfPosition);
  } else if (selfPosition.x < 0) {
    selfPosition.x = 1600.0f;
    // selfPosition.y = std::rand() % 900;
    this->mesh_->SetPosition(selfPosition);
  }
  if (selfPosition.y > 900) {
    selfPosition.y = 0.0f;
    // selfPosition.x = std::rand() % 1600;
    this->mesh_->SetPosition(selfPosition);
  } else if (selfPosition.y < 0) {
    selfPosition.y = 900.0f;
    // selfPosition.x = std::rand() % 1600;
    this->mesh_->SetPosition(selfPosition);
  }
}

void Boids::BlendColors(const std::vector<DroneData*>* const drones,
                        unsigned int selfID,
                        const float& ratio) const noexcept {
  ZoneScopedN("Boids::BlendColors");
  if (drones->size() == 0) return;

  Vector3<float> colorSum;
  float colorAmount = 0.0f;
  for (DroneData* droneData : *drones) {
    if (droneData->id == selfID) continue;

    Mesh* droneMesh = droneData->drone->GetMesh();
    float selfRotation = this->mesh_->GetRotation();
    float droneRotation = droneMesh->GetRotation();

    if (selfRotation < droneRotation + 5.0f &&
        selfRotation > droneRotation - 5.0f) {
      colorSum += droneMesh->GetColor();
      colorAmount++;
    }
  }
  if (colorAmount > 0) {
    Vector3<float> newColor = colorSum / colorAmount;
    // this->mesh_->SetColor(this->mesh_->GetColor().Lerp(newColor, ratio));
    const glm::vec3 color = glm::mix(this->mesh_->GetColor().ToGLMVec3f(),
                                     newColor.ToGLMVec3f(), ratio);
    this->mesh_->SetColor(color.x, color.y, color.z);
  }
}

Boids::Boids(Vector<float> position, Vector<float> scale)
    : Drone(position, scale, Vector3<float>(1.0f, 1.0f, 1.0f)) {}

Boids::Boids(Vector<float> position, Vector<float> scale, Vector3<float> color)
    : Drone(position, scale, color) {}

Boids::~Boids() {}
