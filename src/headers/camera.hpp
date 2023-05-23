#ifndef CAMERA_HPP_
#define CAMERA_HPP_

// Libs
#include "../libs/glm/mat4x4.hpp"
#include "../libs/glm/gtc/matrix_transform.hpp"
// Custom
#include "vector.hpp"

class Camera {
 private:
  Vector<int> windowSize_;
  glm::mat4x4* orthoMatrix_ = nullptr;
  glm::mat4x4* viewMatrix_ = nullptr;
  Vector3<float> position_;
  float near_;
  float far_;
  bool isDirty_;

 public:
  Camera(Vector<int> windowSize, float near, float far);
  ~Camera();

  void Recalculate() noexcept;
  glm::mat4x4* GetOrthoMatrix() const noexcept;
  glm::mat4x4* GetViewMatrix() const noexcept;
};
#endif  // CAMERA_HPP_