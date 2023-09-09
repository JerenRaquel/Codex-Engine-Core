#include "util/vector2.hpp"

template <typename T>
Vector2<T>::Vector2() : x(0), y(0) {}

template <typename T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

template <typename T>
Vector2<T>::~Vector2() {}

template <typename T>
glm::vec3 Vector2<T>::ToGLMVec3f() const noexcept {
  return glm::vec3(x, y, 0);
}

template <typename T>
float Vector2<T>::ToDegreeAngle() const noexcept {
  if (this->x == 0.0f && this->y == 0.0f) {
    return 0.0f;
  }
  return glm::degrees(atan2(this->x, this->y));
}

template <typename T>
float Vector2<T>::Distance(const Vector2<T>& other) const noexcept {
  return sqrt(this->SqrDistance(other));
}

template <typename T>
float Vector2<T>::SqrDistance(const Vector2<T>& other) const noexcept {
  if (*this == other) return 0.0f;

  Vector2<T> difference = other - *this;
  float x = difference.x;
  float y = difference.y;
  return x * x + y * y;
}

template <typename T>
float Vector2<T>::Dot(const Vector2<T>& other) const noexcept {
  return this->x * other.x + this->y * other.y;
}

template <typename T>
bool Vector2<T>::IsWithinSqrDistance(const Vector2<T>& other,
                                     T range) const noexcept {
  if (this->x < (other.x - range) || this->x > (other.x + range) ||
      this->y < (other.y - range) || this->y > (other.y + range)) {
    return false;
  }
  // Vector2<T> difference = other - *this;
  // T sqrd = difference.Dot(difference);
  T sqrd = this->SqrDistance(other);
  return sqrd <= range * range;
}

template <typename T>
bool Vector2<T>::IsWithinSqrDistance(const Vector2<T>& other, T range,
                                     T& sqrDistance) const noexcept {
  if (this->x < (other.x - range) || this->x > (other.x + range) ||
      this->y < (other.y - range) || this->y > (other.y + range)) {
    return false;
  }
  Vector2<T> difference = other - *this;
  sqrDistance = difference.Dot(difference);
  return sqrDistance <= range * range;
}

template <typename T>
bool Vector2<T>::IsWithinDistance(const Vector2<T>& other, float padding,
                                  float& distance) const noexcept {
  if (this->x < (other.x - padding) || this->x > (other.x + padding) ||
      this->y < (other.y - padding) || this->y > (other.y + padding)) {
    return false;
  }
  distance = this->Distance(other);
  return distance <= padding;
}

template <typename T>
bool Vector2<T>::IsWithinBoxDistance(const Vector2<T>& center,
                                     float padding) const noexcept {
  return this->IsWithinRectDistance(center, padding, padding);
}

template <typename T>
bool Vector2<T>::IsWithinRectDistance(const Vector2<T>& center, float xPadding,
                                      float yPadding) const noexcept {
  if (this->x < (center.x - xPadding) || this->x > (center.x + xPadding) ||
      this->y < (center.y - yPadding) || this->y > (center.y + yPadding)) {
    return false;
  }
  return true;
}

template <typename T>
bool Vector2<T>::operator==(const Vector2<T>& other) const noexcept {
  return (this->x == other.x && this->y == other.y);
}

template <typename T>
bool Vector2<T>::operator!=(const Vector2<T>& other) const noexcept {
  return !(*this == other);
}

template <typename T>
Vector2<T> Vector2<T>::operator=(const Vector2<T>& other) noexcept {
  this->x = other.x;
  this->y = other.y;
  return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const noexcept {
  return Vector2<T>(this->x + other.x, this->y + other.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator+=(const Vector2<T>& other) noexcept {
  *this = *this + other;
  return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const noexcept {
  return Vector2<T>(this->x - other.x, this->y - other.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const T& other) const noexcept {
  return Vector2<T>(this->x - other, this->y - other);
}

template <typename T>
Vector2<T> Vector2<T>::operator-=(const Vector2<T>& other) noexcept {
  *this = *this - other;
  return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const T& other) const {
  if (other == 0) {
    throw std::invalid_argument("Divide by zero exception");
  }

  return Vector2<T>(this->x / other, this->y / other);
}

template <typename T>
Vector2<T> Vector2<T>::operator/=(const T& other) {
  *this = *this / other;
  return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const T& other) const noexcept {
  return Vector2<T>(this->x * other, this->y * other);
}

//
// Instantiate the template
//
template class Vector2<int>;
template class Vector2<float>;
