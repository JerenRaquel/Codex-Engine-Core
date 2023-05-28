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
  Vector<float> selfPosition = *(this->GetPosition());

  ZoneScopedN("Boids::DroneFetching");
  const auto alphas = engine->GetDroneManager()->GetDronesByTag("Alpha");
  const auto boids = engine->GetDroneManager()->GetTaggedPositions("Boids");
  const auto closestAlpha =
      engine->GetDroneManager()->GetClosestDrone(alphas, selfPosition);

  // Fly towards closest alpha
  Vector<float> towardsAlpha =
      *(closestAlpha->drone->GetPosition()) - *(this->GetPosition());
  this->mesh_->RotateTowards(towardsAlpha, this->targetBias);

  // Fly with other drones
  Avoidance(boids);
  Cohesion(boids);

  // Fly forwards
  Move();
}

void Boids::Avoidance(std::vector<Vector<float>*>* positions) const noexcept {
  DataStream<Vector<float>>* const dataStream =
      new DataStream<Vector<float>>(positions);

  Vector<float> avgPosition =
      dataStream
          ->FilterAgainst(this->position_,
                          [](auto value, auto other) {
                            if (*(value) == *(other)) return false;
                            if (other->IsWithinSqrDistance(*value, 20.0f))
                              return true;
                            return false;
                          })
          ->Average(Vector<float>(0.0f, 0.0f));
  delete dataStream;

  this->mesh_->RotateTowards(*(this->position_) - avgPosition,
                             this->separationBias);
}

void Boids::Cohesion(std::vector<Vector<float>*>* positions) const noexcept {
  DataStream<Vector<float>>* const dataStream =
      new DataStream<Vector<float>>(positions);

  Vector<float> avgPosition =
      dataStream
          ->FilterAgainst(this->position_,
                          [](auto value, auto other) {
                            if (*(value) == *(other)) return false;
                            if (other->IsWithinSqrDistance(*value, 20.0f))
                              return true;
                            return false;
                          })
          ->Average(Vector<float>(0.0f, 0.0f));
  delete dataStream;

  this->mesh_->RotateTowards(avgPosition - *(this->position_),
                             this->cohesionBias);
}

void Boids::Move() const noexcept {
  ZoneScopedN("Boids::Move");
  this->mesh_->Translate(this->mesh_->GetDirectionVector(), this->flySpeed);

  // Bounds
  Vector<float> selfPosition = *(this->GetPosition());
  if (selfPosition.x > 1600) {
    selfPosition.x = 0.0f;
    this->mesh_->SetPosition(selfPosition);
  } else if (selfPosition.x < 0) {
    selfPosition.x = 1600.0f;
    this->mesh_->SetPosition(selfPosition);
  }
  if (selfPosition.y > 900) {
    selfPosition.y = 0.0f;
    this->mesh_->SetPosition(selfPosition);
  } else if (selfPosition.y < 0) {
    selfPosition.y = 900.0f;
    this->mesh_->SetPosition(selfPosition);
  }
}

Boids::Boids(Vector<float>* position, Vector<float> scale)
    : Drone(position, scale, Vector3<float>(1.0f, 1.0f, 1.0f)) {}

Boids::Boids(Vector<float>* position, Vector<float> scale, Vector3<float> color)
    : Drone(position, scale, color) {}

Boids::~Boids() {}
