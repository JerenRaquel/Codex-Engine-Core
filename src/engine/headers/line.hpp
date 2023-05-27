#ifndef LINE_HPP_
#define LINE_HPP_

// Custom
#include "vector.hpp"
// Lib
#include "../../libs/glm/mat4x4.hpp"
#include "../../libs/glm/gtc/matrix_transform.hpp"

class Line {
 private:
  Vector<float> start_;
  Vector<float> end_;

  int Orientation(const Vector<float>& a, const Vector<float>& b,
                  const Vector<float>& c) const noexcept;
  bool OnSegment(const Vector<float>& a, const Vector<float>& b,
                 const Vector<float>& c) const noexcept;

 public:
  Line(const Vector<float>& start, const Vector<float>& end);
  ~Line();

  bool IsIntersecting(const Line& other) const noexcept;
  const Vector<float>& GetStart() const noexcept;
  const Vector<float>& GetEnd() const noexcept;

  Line operator=(const Line& other) noexcept;
  Line operator*(const glm::mat4x4* const modelMatrix) const noexcept;
};
#endif  // LINE_HPP_