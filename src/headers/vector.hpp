#ifndef VECTOR_HPP_
#define VECTOR_HPP_

// Lib
#include "../libs/glm/vec3.hpp"

template <typename T>
class Vector {
 public:
  T x, y;

  Vector<T>();
  Vector<T>(T x, T y);
  ~Vector<T>();

  glm::vec3 ToGLMVec3f() const noexcept { return glm::vec3(x, y, 0); }

  Vector<T> operator=(const Vector<T>& other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
  }

  Vector<T> operator/(const T& other) {
    this->x /= other;
    this->y /= other;
    return *this;
  }
};

template <typename T>
class Vector3 {
 public:
  T x, y, z;

  Vector3<T>();
  Vector3<T>(T x, T y, T z);
  ~Vector3<T>();

  glm::vec3 ToGLMVec3f() const noexcept { return glm::vec3(x, y, z); }

  Vector3<T> operator=(const Vector3<T>& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
  }
};

#endif  // VECTOR_HPP_