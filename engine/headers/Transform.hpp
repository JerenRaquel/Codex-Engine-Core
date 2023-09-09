#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

// Lib
#include "mat4x4.hpp"
// Custom
#include "util/vector3.hpp"

class Transform {
 private:
  glm::mat4x4* modelMatrix_;
  bool isModelMatrixDirty_;
  Vector2<float> position_;
  Vector2<float> scale_;
  float rotation_;

 public:
  Transform(const Vector2<float>& position)
      : Transform(position, Vector2<float>(1.0f, 1.0f), 0) {}
  Transform(const Vector2<float>& position, const Vector2<float>& scale)
      : Transform(position, scale, 0) {}
  Transform(const Vector2<float>& position, const Vector2<float>& scale,
            const float& rotation);
  ~Transform();

  // Utility
  Transform* const RandomizeRotation() noexcept;
  Transform* const Rotate(const float& angle) noexcept;
  Transform* const RotateTowards(const Vector2<float>& direction) noexcept;
  Transform* const RotateTowards(const Vector2<float>& direction,
                                 const float& bais) noexcept;
  Transform* const Translate(const Vector2<float>& offset) noexcept;
  Transform* const Translate(const Vector2<float>& direction,
                             const float& magnitude) noexcept;

  // Setters
  Transform* const SetScale(const Vector2<float>& scale) noexcept;
  Transform* const SetPosition(const Vector2<float>& position) noexcept;
  Transform* const SetPosition(const float& x, const float& y) noexcept;
  Transform* const SetRotation(const float& rotation) noexcept;

  // Getters
  glm::mat4x4* GetModelMatrix() noexcept;
  Vector2<float> GetDirectionVector() const noexcept;
  const float GetRotation() const noexcept;
  Vector2<float> GetScale() const noexcept;
  Vector2<float> GetPosition() const noexcept;
};
#endif  // TRANSFORM_HPP_