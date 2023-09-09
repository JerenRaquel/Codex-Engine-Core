#include "transform.hpp"

Transform::Transform(const Vector2<float>& position, const Vector2<float>& scale,
                     const float& rotation) {
  this->position_ = position;
  this->scale_ = scale;
  this->rotation_ = rotation;
  this->isModelMatrixDirty_ = true;
  this->modelMatrix_ = new glm::mat4x4(1.0f);
}

Transform::~Transform() { delete this->modelMatrix_; }

// Utility
Transform* const Transform::RandomizeRotation() noexcept {
  return this->SetRotation(std::rand() % 360);
}

Transform* const Transform::Rotate(const float& angle) noexcept {
  this->rotation_ += angle;
  this->isModelMatrixDirty_ = true;
  return this;
}

Transform* const Transform::RotateTowards(
    const Vector2<float>& direction) noexcept {
  return this->RotateTowards(direction, 1.0f);
}

Transform* const Transform::RotateTowards(const Vector2<float>& direction,
                                          const float& bais) noexcept {
  float turningAngle = direction.ToDegreeAngle() - this->rotation_;
  if (turningAngle > 180.0f) {
    turningAngle -= 360.0f;
  } else if (turningAngle < -180.0f) {
    turningAngle += 360.0f;
  }

  this->Rotate(turningAngle * bais);
  return this;
}

Transform* const Transform::Translate(const Vector2<float>& offset) noexcept {
  this->position_ += offset;
  this->isModelMatrixDirty_ = true;
  return this;
}

Transform* const Transform::Translate(const Vector2<float>& direction,
                                      const float& magnitude) noexcept {
  return this->Translate(direction * magnitude);
}

// Setters
Transform* const Transform::SetScale(const Vector2<float>& scale) noexcept {
  this->scale_ = scale;
  this->isModelMatrixDirty_ = true;
  return this;
}

Transform* const Transform::SetPosition(
    const Vector2<float>& position) noexcept {
  return this->SetPosition(position.x, position.y);
}

Transform* const Transform::SetPosition(const float& x,
                                        const float& y) noexcept {
  this->position_.x = x;
  this->position_.y = y;
  this->isModelMatrixDirty_ = true;
  return this;
}

Transform* const Transform::SetRotation(const float& rotation) noexcept {
  this->rotation_ = rotation;
  if (this->rotation_ <= -360.0f) {
    this->rotation_ += 360.0f;
  } else if (this->rotation_ >= 360.0f) {
    this->rotation_ -= 360.0f;
  }
  this->isModelMatrixDirty_ = true;
  return this;
}

// Getters
glm::mat4x4* Transform::GetModelMatrix() noexcept {
  if (this->isModelMatrixDirty_) {
    delete this->modelMatrix_;
    this->modelMatrix_ = new glm::mat4x4(1.0f);
    *(this->modelMatrix_) =
        glm::translate(*this->modelMatrix_, this->position_.ToGLMVec3f());
    *(this->modelMatrix_) =
        glm::rotate(*this->modelMatrix_, glm::radians(this->rotation_),
                    glm::vec3(0, 0, -1));
    *(this->modelMatrix_) =
        glm::scale(*this->modelMatrix_, this->scale_.ToGLMVec3f());

    this->isModelMatrixDirty_ = false;
  }
  return this->modelMatrix_;
}

Vector2<float> Transform::GetDirectionVector() const noexcept {
  return Vector2<float>(glm::cos(glm::radians(-this->rotation_ + 90.0f)),
                       glm::sin(glm::radians(-this->rotation_ + 90.0f)));
}

const float Transform::GetRotation() const noexcept { return this->rotation_; }

Vector2<float> Transform::GetScale() const noexcept { return this->scale_; }

Vector2<float> Transform::GetPosition() const noexcept {
  return this->position_;
}
