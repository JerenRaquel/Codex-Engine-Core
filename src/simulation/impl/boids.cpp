#include "../headers/boids.hpp"

#include "../../../tools/tracy/tracy/Tracy.hpp"

void Boids::InternalStart(Engine* const engine, const std::string& tag,
                          const unsigned int id) {
  if (id < 10) {
    this->mesh_->SetScale(Vector<float>(5.0f, 5.0f));
  }
  float r = static_cast<float>(std::rand() % 255) / 255.0f;
  float g = static_cast<float>(std::rand() % 255) / 255.0f;
  float b = static_cast<float>(std::rand() % 255) / 255.0f;
  this->mesh_->SetColor(Vector3<float>(r, g, b))
      ->SetRotation(std::rand() % 360);
}

void Boids::InternalUpdate(Engine* const engine, const std::string& tag,
                           const unsigned int id) {
  Vector<float> selfPosition = this->mesh_->GetPosition();
  Vector<float> center(800.0f, 450.0f);

  ZoneScopedN("Boids::DroneFetching");
  std::vector<DroneData*>* const allDrones =
      engine->GetDroneManager()->GetAllDrones();
  std::vector<DroneData*>* const drones100 =
      engine->GetDroneManager()->FilterBasedOnRange(allDrones, selfPosition,
                                                    100.0f);
  std::vector<DroneData*>* const drones20 =
      engine->GetDroneManager()->FilterBasedOnRange(drones100, selfPosition,
                                                    20.0f);

  // Fly towards center
  FlyTowardsCenter(center);

  // Fly with other drones
  CohesionAndAvoidance(drones20);

  // Fly forwards
  Move();

  // Drones that flock together have similar colors
  BlendColors(drones100, id);

  delete drones100;
  delete drones20;
}

void Boids::FlyTowardsCenter(const Vector<float>& center) const noexcept {
  ZoneScopedN("Boids::FlyTowardsCenter");
  Vector<float> towardsCenter = center - this->mesh_->GetPosition();
  this->mesh_->RotateTowards(towardsCenter, this->targetBias);
}

void Boids::CohesionAndAvoidance(
    const std::vector<DroneData*>* const drones) const noexcept {
  ZoneScopedN("Boids::CohesionAndAvoidance");
  if (drones->size() > 0) {
    float sum = 0.0f;
    for (DroneData* droneData : *drones) {
      Mesh* droneMesh = droneData->drone->GetMesh();

      // Avoid other drones
      this->mesh_->RotateTowards(
          this->mesh_->GetPosition() - droneMesh->GetPosition(),
          this->separationBias);

      // Begin aggregation for cohesion
      float bias =
          this->mesh_->GetColor().DifferenceBias(droneMesh->GetColor());
      sum += droneMesh->GetRotation() * (1.0f - bias);
    }
    float average = sum / drones->size();
    float newRotation = average + this->mesh_->GetRotation();
    newRotation /= 77.0f + (std::rand() % 30);
    newRotation -= this->mesh_->GetRotation();
    newRotation *= this->cohesionBias;
    this->mesh_->Rotate(newRotation);
  }
}

void Boids::Move() const noexcept {
  ZoneScopedN("Boids::Move");
  this->mesh_->Translate(this->mesh_->GetDirectionVector(), this->flySpeed);

  // Bounds
  Vector<float> selfPosition = this->mesh_->GetPosition();
  if (selfPosition.x > 1600) {
    selfPosition.x = 0.0f;
    selfPosition.y = std::rand() % 900;
    this->mesh_->SetPosition(selfPosition);
  } else if (selfPosition.x < 0) {
    selfPosition.x = 1600.0f;
    selfPosition.y = std::rand() % 900;
    this->mesh_->SetPosition(selfPosition);
  }
  if (selfPosition.y > 900) {
    selfPosition.y = 0.0f;
    selfPosition.x = std::rand() % 1600;
    this->mesh_->SetPosition(selfPosition);
  } else if (selfPosition.y < 0) {
    selfPosition.y = 900.0f;
    selfPosition.x = std::rand() % 1600;
    this->mesh_->SetPosition(selfPosition);
  }
}

void Boids::BlendColors(const std::vector<DroneData*>* const drones,
                        unsigned int selfID) const noexcept {
  ZoneScopedN("Boids::BlendColors");
  if (selfID >= 10 && drones->size() > 0) {
    Vector3<float> colorSum;
    float colorAmount = 0.0f;
    for (DroneData* droneData : *drones) {
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
      this->mesh_->SetColor(this->mesh_->GetColor().Lerp(newColor, 0.5f));
    }
  }
}

Boids::Boids(Vector<float> position, Vector<float> scale)
    : Drone(position, scale, Vector3<float>(1.0f, 1.0f, 1.0f)) {}

Boids::Boids(Vector<float> position, Vector<float> scale, Vector3<float> color)
    : Drone(position, scale, color) {}

Boids::~Boids() {}
