#ifndef VECTOR_HPP_
#define VECTOR_HPP_

class Vector2 {
 private:
  // member vars

 public:
  float x, y;

  Vector2();
  Vector2(float x, float y);
  ~Vector2();

  Vector2 operator=(const Vector2& other) {
    this->x = other.x;
    this->y = other.y;
  }
};
#endif  // VECTOR_HPP_