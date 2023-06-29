#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

// Engine
#include "util/vector2.hpp"

template <typename T>
class Vector3 : public Vector2<T> {
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
  Vector3<T> operator=(const glm::vec3& other) noexcept;
  Vector3<T> operator=(const Vector2<T>& other) noexcept;
  Vector3<T> operator+(const Vector3<T>& other) const noexcept;
  Vector3<T> operator+=(const Vector3<T>& other) noexcept;
  Vector3<T> operator-(const Vector3<T>& other) const noexcept;
  Vector3<T> operator/(const T& other) const;
  Vector3<T> operator/=(const T& other);
  Vector3<T> operator*(const T& other) const noexcept;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector3<T>& vector) {
  os << "Vector3(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
  return os;
}
#endif  // VECTOR3_HPP_