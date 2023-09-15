#include "colliders/boxCollider.hpp"

BoxCollider::BoxCollider(Transform* const transform) : transform_(transform) {
  this->Update();
}

BoxCollider::~BoxCollider() {}

// Utility
bool BoxCollider::IsCollidingInsideOther(
    const BoxCollider& other) const noexcept {
  float dx = abs(other.GetPointA().x - other.GetPointB().x);
  float dy = abs(other.GetPointA().y - other.GetPointC().y);
  for (int i = 0; i < 4; i++) {
    if (this->operator[](i).IsWithinSqrDistance(other.GetCenter(), dx, dy)) {
      return true;
    }
  }
  return false;
}

void BoxCollider::Update() noexcept {}

// Getters
Vector2<float> BoxCollider::GetPointA() const noexcept { return this->pointA_; }

Vector2<float> BoxCollider::GetPointB() const noexcept { return this->pointB_; }

Vector2<float> BoxCollider::GetPointC() const noexcept { return this->pointC_; }

Vector2<float> BoxCollider::GetPointD() const noexcept { return this->pointD_; }

Vector2<float> BoxCollider::GetCenter() const noexcept {
  return this->transform_->GetPosition();
}
