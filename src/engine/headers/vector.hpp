#ifndef VECTOR_HPP_
#define VECTOR_HPP_

// Std
#include <cmath>
#include <stdexcept>
#include <iostream>
// Lib
#include "../../libs/glm/vec3.hpp"
#include "../../libs/glm/gtc/matrix_transform.hpp"

template <typename T>
class Vector {
 public:
  T x, y;

  Vector<T>();
  Vector<T>(T x, T y);
  ~Vector<T>();

  glm::vec3 ToGLMVec3f() const noexcept;
  float ToDegreeAngle() const noexcept;
  float Distance(const Vector<T>& other) const noexcept;
  float SqrDistance(const Vector<T>& other) const noexcept;
  bool IsWithinDistance(const Vector<T>& other, float padding) const noexcept;
  bool IsWithinDistance(const Vector<T>& other, float padding,
                        float& distance) const noexcept;
  bool IsWithinBoxDistance(const Vector<T>& other,
                           float distance) const noexcept;
  bool IsWithinRectDistance(const Vector<T>& other, float xPadding,
                            float yPadding) const noexcept;

  bool operator==(const Vector<T>& other) const noexcept;
  bool operator!=(const Vector<T>& other) const noexcept;
  Vector<T> operator=(const Vector<T>& other) noexcept;
  Vector<T> operator+(const Vector<T>& other) const noexcept;
  Vector<T> operator+=(const Vector<T>& other) noexcept;
  Vector<T> operator-(const Vector<T>& other) const noexcept;
  Vector<T> operator-(const T& other) const noexcept;
  Vector<T> operator/(const T& other) const;
  Vector<T> operator/=(const T& other);
  Vector<T> operator*(const T& other) const noexcept;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
  os << "Vector(" << vector.x << ", " << vector.y << ")";
  return os;
}

template <typename T>
class Vector3 : public Vector<T> {
 public:
  T z;

  Vector3<T>();
  Vector3<T>(T x, T y, T z);
  ~Vector3<T>();

  glm::vec3 ToGLMVec3f() const noexcept;
  Vector3<T> Lerp(const Vector3<T>& other, float rate) const noexcept;
  float DifferenceBias(const Vector3<T>& other) const noexcept;

  bool operator==(const Vector3<T>& other) const noexcept;
  bool operator!=(const Vector3<T>& other) const noexcept;
  Vector3<T> operator=(const Vector3<T>& other) noexcept;
  Vector3<T> operator=(const Vector<T>& other) noexcept;
  Vector3<T> operator+(const Vector3<T>& other) const noexcept;
  Vector3<T> operator+=(const Vector3<T>& other) noexcept;
  Vector3<T> operator-(const Vector3<T>& other) const noexcept;
  Vector3<T> operator/(const T& other) const;
  Vector3<T> operator/=(const T& other);
  Vector3<T> operator*(const T& other) const noexcept;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector3<T>& vector) {
  os << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
  return os;
}

#endif  // VECTOR_HPP_