#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

// Std
#include <cmath>
#include <stdexcept>
#include <iostream>
// Lib
#include "vec3.hpp"
#include "gtc/matrix_transform.hpp"

template <typename T>
class Vector2 {
 public:
  T x, y;

  Vector2<T>();
  Vector2<T>(T x, T y);
  ~Vector2<T>();

  glm::vec3 ToGLMVec3f() const noexcept;
  float ToDegreeAngle() const noexcept;
  float Distance(const Vector2<T>& other) const noexcept;
  float SqrDistance(const Vector2<T>& other) const noexcept;
  float Dot(const Vector2<T>& other) const noexcept;
  bool IsWithinSqrDistance(const Vector2<T>& other, T range) const noexcept;
  bool IsWithinSqrDistance(const Vector2<T>& other, T range,
                           T& sqrDistance) const noexcept;
  bool IsWithinDistance(const Vector2<T>& other, float padding,
                        float& distance) const noexcept;
  bool IsWithinBoxDistance(const Vector2<T>& other,
                           float distance) const noexcept;
  bool IsWithinRectDistance(const Vector2<T>& other, float xPadding,
                            float yPadding) const noexcept;

  bool operator==(const Vector2<T>& other) const noexcept;
  bool operator!=(const Vector2<T>& other) const noexcept;
  Vector2<T> operator=(const Vector2<T>& other) noexcept;
  Vector2<T> operator+(const Vector2<T>& other) const noexcept;
  Vector2<T> operator+=(const Vector2<T>& other) noexcept;
  Vector2<T> operator-(const Vector2<T>& other) const noexcept;
  Vector2<T> operator-(const T& other) const noexcept;
  Vector2<T> operator-=(const Vector2<T>& other) noexcept;
  Vector2<T> operator/(const T& other) const;
  Vector2<T> operator/=(const T& other);
  Vector2<T> operator*(const T& other) const noexcept;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vector) {
  os << "Vector2(" << vector.x << ", " << vector.y << ")";
  return os;
}

#endif  // VECTOR2_HPP_