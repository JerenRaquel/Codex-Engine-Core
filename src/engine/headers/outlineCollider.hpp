#ifndef OUTLINECOLLIDER_HPP_
#define OUTLINECOLLIDER_HPP_

// Std
#include <vector>
// Custom
#include "vector.hpp"
#include "line.hpp"
// Lib
#include "mat4x4.hpp"

class OutlineCollider {
 private:
  std::vector<Line*>* lines_ = nullptr;

 public:
  OutlineCollider(const float* const vertices, const unsigned int& verticesSize,
                  const std::vector<unsigned int>& verticesOrder);
  ~OutlineCollider();

  bool IsColliding(const glm::mat4x4* const modelMatrix,
                   const Line& other) const noexcept;
};
#endif  // OUTLINECOLLIDER_HPP_