#ifndef CAMERA_HPP_
#define CAMERA_HPP_

// Libs
#include "../libs/glm/mat4x4.hpp"
#include "../libs/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/gtc/type_ptr.hpp"
// Custom
#include "vector.hpp"

class Camera {
 private:
  Vector<int> windowSize_;
  glm::mat4x4 orthoMatrix_;
  glm::mat4x4 viewMatrix_;
  Vector3<float> position_;
  Vector3<float> target_;
  Vector3<float> up_;
  bool isDirty_;

 public:
  Camera(Vector<int> windowSize);
  ~Camera();

  void Recalculate() noexcept;
  float* GetOrthoMatrix() const noexcept;
  float* GetViewMatrix() const noexcept;
};
#endif  // CAMERA_HPP_