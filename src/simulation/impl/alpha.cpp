#include "../headers/alpha.hpp"

void Alpha::InternalStart(Engine* const engine, const std::string& tag,
                          const unsigned int id) {
  float r = static_cast<float>(std::rand() % 255) / 255.0f;
  float g = static_cast<float>(std::rand() % 255) / 255.0f;
  float b = static_cast<float>(std::rand() % 255) / 255.0f;
  this->material_->SetColor(r, g, b);
  this->transform_->SetRotation(std::rand() % 360);
}

void Alpha::InternalUpdate(Engine* const engine, const std::string& tag,
                           const unsigned int id) {
  // Fly towards center
  Vector<float> towardsCenter =
      Vector<float>(800.0f, 450.0f) - *(this->GetPosition());
  this->transform_->RotateTowards(towardsCenter, this->targetBias);

  // Avoid other alphas
  Avoidance(engine->GetDroneManager()->GetTaggedPositions("Alpha"));

  // Move
  Move();
}

void Alpha::Move() const noexcept {
  this->transform_->Translate(this->transform_->GetDirectionVector(),
                              this->flySpeed);

  // Bounds
  Vector<float> selfPosition = *(this->GetPosition());
  if (selfPosition.x > 1650) {
    selfPosition.x = 0.0f;
    this->transform_->SetPosition(selfPosition);
  } else if (selfPosition.x < -50) {
    selfPosition.x = 1600.0f;
    this->transform_->SetPosition(selfPosition);
  }
  if (selfPosition.y > 950) {
    selfPosition.y = 0.0f;
    this->transform_->SetPosition(selfPosition);
  } else if (selfPosition.y < -50) {
    selfPosition.y = 900.0f;
    this->transform_->SetPosition(selfPosition);
  }
}

void Alpha::Avoidance(
    std::vector<Vector<float>*>* const dronePositions) const noexcept {
  DataStream<Vector<float>>* const dataStream =
      new DataStream<Vector<float>>(dronePositions);

  Vector<float> avgPosition =
      dataStream
          ->FilterAgainst(
              this->GetPosition(),
              [](const Vector<float>* value, const Vector<float>* other) {
                if (*(value) == *(other)) return false;
                if (value->SqrDistance(*other) > 400.0f) return false;
                return true;
              })
          ->Average(Vector<float>(0.0f, 0.0f));

  if (avgPosition != Vector<float>(0.0f, 0.0f)) {
    this->transform_->RotateTowards(*(this->GetPosition()) - avgPosition,
                                    this->separationBias);
  }
  delete dataStream;
}

Alpha::Alpha(Vector<float>* position, Vector<float> scale)
    : Drone(position, scale, Vector3<float>(1.0f, 1.0f, 1.0f)) {}

Alpha::Alpha(Vector<float>* position, Vector<float> scale, Vector3<float> color)
    : Drone(position, scale, color) {}

Alpha::~Alpha() {}
