#ifndef LINE_HPP_
#define LINE_HPP_

// Custom
#include "util/vector3.hpp"
// Lib
#include "mat4x4.hpp"
#include "gtc/matrix_transform.hpp"

class Line {
 private:
  Vector2<float> start_;
  Vector2<float> end_;

  int Orientation(const Vector2<float>& a, const Vector2<float>& b,
                  const Vector2<float>& c) const noexcept;
  bool OnSegment(const Vector2<float>& a, const Vector2<float>& b,
                 const Vector2<float>& c) const noexcept;

 public:
  Line(const Vector2<float>& start, const Vector2<float>& end);
  ~Line();

  bool IsIntersecting(const Line& other) const noexcept;
  const Vector2<float>& GetStart() const noexcept;
  const Vector2<float>& GetEnd() const noexcept;

  Line operator=(const Line& other) noexcept;
  Line operator*(const glm::mat4x4* const modelMatrix) const noexcept;
};
#endif  // LINE_HPP_