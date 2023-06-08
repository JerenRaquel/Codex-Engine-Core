#include "util/vector.hpp"

//
// Vector
//
template <typename T>
Vector<T>::Vector() : x(0), y(0) {}

template <typename T>
Vector<T>::Vector(T x, T y) : x(x), y(y) {}

template <typename T>
Vector<T>::~Vector() {}

template <typename T>
glm::vec3 Vector<T>::ToGLMVec3f() const noexcept {
  return glm::vec3(x, y, 0);
}

template <typename T>
float Vector<T>::ToDegreeAngle() const noexcept {
  if (this->x == 0.0f && this->y == 0.0f) {
    return 0.0f;
  }
  return glm::degrees(atan2(this->x, this->y));
}

template <typename T>
float Vector<T>::Distance(const Vector<T>& other) const noexcept {
  return sqrt(this->SqrDistance(other));
}

template <typename T>
float Vector<T>::SqrDistance(const Vector<T>& other) const noexcept {
  if (*this == other) return 0.0f;

  Vector<T> difference = other - *this;
  float x = difference.x;
  float y = difference.y;
  return x * x + y * y;
}

template <typename T>
float Vector<T>::Dot(const Vector<T>& other) const noexcept {
  return this->x * other.x + this->y * other.y;
}

template <typename T>
bool Vector<T>::IsWithinSqrDistance(const Vector<T>& other,
                                    T range) const noexcept {
  if (this->x < (other.x - range) || this->x > (other.x + range) ||
      this->y < (other.y - range) || this->y > (other.y + range)) {
    return false;
  }
  // Vector<T> difference = other - *this;
  // T sqrd = difference.Dot(difference);
  T sqrd = this->SqrDistance(other);
  return sqrd <= range * range;
}

template <typename T>
bool Vector<T>::IsWithinSqrDistance(const Vector<T>& other, T range,
                                    T& sqrDistance) const noexcept {
  if (this->x < (other.x - range) || this->x > (other.x + range) ||
      this->y < (other.y - range) || this->y > (other.y + range)) {
    return false;
  }
  Vector<T> difference = other - *this;
  sqrDistance = difference.Dot(difference);
  return sqrDistance <= range * range;
}

template <typename T>
bool Vector<T>::IsWithinDistance(const Vector<T>& other, float padding,
                                 float& distance) const noexcept {
  if (this->x < (other.x - padding) || this->x > (other.x + padding) ||
      this->y < (other.y - padding) || this->y > (other.y + padding)) {
    return false;
  }
  distance = this->Distance(other);
  return distance <= padding;
}

template <typename T>
bool Vector<T>::IsWithinBoxDistance(const Vector<T>& center,
                                    float padding) const noexcept {
  return this->IsWithinRectDistance(center, padding, padding);
}

template <typename T>
bool Vector<T>::IsWithinRectDistance(const Vector<T>& center, float xPadding,
                                     float yPadding) const noexcept {
  if (this->x < (center.x - xPadding) || this->x > (center.x + xPadding) ||
      this->y < (center.y - yPadding) || this->y > (center.y + yPadding)) {
    return false;
  }
  return true;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const noexcept {
  return (this->x == other.x && this->y == other.y);
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& other) const noexcept {
  return !(*this == other);
}

template <typename T>
Vector<T> Vector<T>::operator=(const Vector<T>& other) noexcept {
  this->x = other.x;
  this->y = other.y;
  return *this;
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const noexcept {
  return Vector<T>(this->x + other.x, this->y + other.y);
}

template <typename T>
Vector<T> Vector<T>::operator+=(const Vector<T>& other) noexcept {
  *this = *this + other;
  return *this;
}

template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) const noexcept {
  return Vector<T>(this->x - other.x, this->y - other.y);
}

template <typename T>
Vector<T> Vector<T>::operator-(const T& other) const noexcept {
  return Vector<T>(this->x - other, this->y - other);
}

template <typename T>
Vector<T> Vector<T>::operator-=(const Vector<T>& other) noexcept {
  *this = *this - other;
  return *this;
}

template <typename T>
Vector<T> Vector<T>::operator/(const T& other) const {
  if (other == 0) {
    throw std::invalid_argument("Divide by zero exception");
  }

  return Vector<T>(this->x / other, this->y / other);
}

template <typename T>
Vector<T> Vector<T>::operator/=(const T& other) {
  *this = *this / other;
  return *this;
}

template <typename T>
Vector<T> Vector<T>::operator*(const T& other) const noexcept {
  return Vector<T>(this->x * other, this->y * other);
}

//
// Vector3
//
template <typename T>
Vector3<T>::Vector3() : Vector<T>(), z(0) {}

template <typename T>
Vector3<T>::Vector3(T x, T y, T z) : Vector<T>(x, y), z(z) {}

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
Vector3<T> Vector3<T>::operator=(const Vector<T>& other) noexcept {
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
template class Vector<int>;
template class Vector<float>;
template class Vector3<int>;
template class Vector3<float>;