#include "util/vector3.hpp"

template <typename T>
Vector3<T>::Vector3() : Vector2<T>(), z(0) {}

template <typename T>
Vector3<T>::Vector3(T x, T y, T z) : Vector2<T>(x, y), z(z) {}

template <typename T>
Vector3<T>::~Vector3() {}

template <typename T>
glm::vec3 Vector3<T>::ToGLMVec3f() const noexcept {
  return glm::vec3(this->x, this->y, this->z);
}

template <typename T>
Vector3<T> Vector3<T>::Lerp(const Vector3<T>& other,
                            float rate) const noexcept {
  return Vector3<T>(this->x + (other.x - this->x) * rate,
                    this->y + (other.y - this->y) * rate,
                    this->z + (other.z - this->z) * rate);
}

template <typename T>
float Vector3<T>::DifferenceBias(const Vector3<T>& other) const noexcept {
  Vector3<T> difference = other - *this;
  float sum = difference.x + difference.y + difference.z;
  return sum / 3.0f;
}

template <typename T>
bool Vector3<T>::operator==(const Vector3<T>& other) const noexcept {
  return (this->x == other.x && this->y == other.y && this->z == other.z);
}

template <typename T>
bool Vector3<T>::operator!=(const Vector3<T>& other) const noexcept {
  return !(*this == other);
}

template <typename T>
Vector3<T> Vector3<T>::operator=(const Vector3<T>& other) noexcept {
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}

template <typename T>
Vector3<T> Vector3<T>::operator=(const glm::vec3& other) noexcept {
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}

template <typename T>
Vector3<T> Vector3<T>::operator=(const Vector2<T>& other) noexcept {
  this->x = other.x;
  this->y = other.y;
  return *this;
}

template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& other) const noexcept {
  return Vector3<T>(this->x + other.x, this->y + other.y, this->z + other.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator+=(const Vector3<T>& other) noexcept {
  *this = *this + other;
  return *this;
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& other) const noexcept {
  return Vector3<T>(this->x - other.x, this->y - other.y, this->z - other.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const T& other) const {
  if (other == 0) {
    throw std::invalid_argument("Divide by zero exception");
  }

  return Vector3<T>(this->x / other, this->y / other, this->z / other);
}

template <typename T>
Vector3<T> Vector3<T>::operator/=(const T& other) {
  *this = *this / other;
  return *this;
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const T& other) const noexcept {
  return Vector3<T>(this->x * other, this->y * other, this->z * other);
}

//
// Instantiate the template
//
template class Vector3<int>;
template class Vector3<float>;