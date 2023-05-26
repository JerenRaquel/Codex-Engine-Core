#include "../headers/alpha.hpp"

void Alpha::InternalStart(Engine* const engine, const std::string& tag,
                          const unsigned int id) {
  float r = static_cast<float>(std::rand() % 255) / 255.0f;
  float g = static_cast<float>(std::rand() % 255) / 255.0f;
  float b = static_cast<float>(std::rand() % 255) / 255.0f;
  this->mesh_->SetColor(Vector3<float>(r, g, b))
      ->SetRotation(std::rand() % 360);
}

void Alpha::InternalUpdate(Engine* const engine, const std::string& tag,
                           const unsigned int id) {
  // Fly towards center
  Vector<float> towardsCenter =
      Vector<float>(800.0f, 450.0f) - this->mesh_->GetPosition();
  this->mesh_->RotateTowards(towardsCenter, this->targetBias);

  // Avoid other alphas
  const auto alphas = engine->GetDroneManager()->GetDronesByTag("Alpha");
  Avoidance(alphas, id);

  // Move
  Move();
}

void Alpha::Move() const noexcept {
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

void Alpha::Avoidance(const std::vector<DroneData*>* const drones,
                      const unsigned int& selfID) const noexcept {
  if (drones->size() == 0) return;

  for (DroneData* droneData : *drones) {
    if (droneData->id == selfID) continue;
    Vector<float> dronePosition = droneData->drone->GetMesh()->GetPosition();
    if (this->mesh_->GetPosition().SqrDistance(dronePosition) > 40000.0f) {
      continue;
    }

    this->mesh_->RotateTowards(this->mesh_->GetPosition() - dronePosition,
                               this->separationBias);
  }
}

Alpha::Alpha(Vector<float> position, Vector<float> scale)
    : Drone(position, scale, Vector3<float>(1.0f, 1.0f, 1.0f)) {}

Alpha::Alpha(Vector<float> position, Vector<float> scale, Vector3<float> color)
    : Drone(position, scale, color) {}

Alpha::~Alpha() {}
