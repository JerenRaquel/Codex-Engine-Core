#ifndef QUAD_HPP_
#define QUAD_HPP_

// Custom
#include "vector.hpp"

class Quad {
 private:
  Vector2 position_;
  Vector2 size_;

 public:
  Quad();
  Quad(const Vector2& size);
  Quad(const Vector2& size, const Vector2& position);
  ~Quad();
};
#endif  // QUAD_HPP_