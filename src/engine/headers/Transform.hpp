#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

// Lib
#include "mat4x4.hpp"
// Custom
#include "vector.hpp"

class Transform {
 private:
  glm::mat4x4* modelMatrix_;
  bool isModelMatrixDirty_;
  Vector<float>* position_;
  Vector<float> scale_;
  float rotation_;

 public:
  Transform(Vector<float>* const position)
      : Transform(position, Vector<float>(1.0f, 1.0f), 0) {}
  Transform(Vector<float>* const position, const Vector<float>& scale)
      : Transform(position, scale, 0) {}
  Transform(Vector<float>* const position, const Vector<float>& scale,
            const float& rotation);
  ~Transform();

  // Utility
  Transform* const RandomizeRotation() noexcept;
  Transform* const Rotate(const float& angle) noexcept;
  Transform* const RotateTowards(const Vector<float>& direction) noexcept;
  Transform* const RotateTowards(const Vector<float>& direction,
                                 const float& bais) noexcept;
  Transform* const Translate(const Vector<float>& direction,
                             const float& magnitude) noexcept;

  // Setters
  Transform* const SetScale(const Vector<float>& scale) noexcept;
  Transform* const SetPosition(const Vector<float>& position) noexcept;
  Transform* const SetPosition(const float& x, const float& y) noexcept;
  Transform* const SetRotation(const float& rotation) noexcept;

  // Getters
  glm::mat4x4* GetModelMatrix() noexcept;
  Vector<float> GetDirectionVector() const noexcept;
  const float GetRotation() const noexcept;
  Vector<float> GetScale() const noexcept;
  Vector<float>* const GetPosition() const noexcept;
};
#endif  // TRANSFORM_HPP_