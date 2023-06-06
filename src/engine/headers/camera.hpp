#ifndef CAMERA_HPP_
#define CAMERA_HPP_

// Libs
#include "mat4x4.hpp"
#include "gtc/matrix_transform.hpp"
// Custom
#include "vector.hpp"

class Camera {
 private:
  Vector<int> windowSize_;
  glm::mat4x4* orthoMatrix_ = nullptr;
  glm::mat4x4* viewMatrix_ = nullptr;
  glm::mat4x4* orthoViewMatrix_ = nullptr;
  Vector3<float> position_;
  float cameraSpeed_ = 5.0f;
  float near_;
  float far_;
  bool isOrthoDirty_ = true;
  bool isViewDirty_ = true;
  bool isOrthoViewDirty_ = true;

 public:
  Camera(Vector<int> windowSize, float near, float far);
  ~Camera();

  // Utility
  void UpdatePosition(const Vector<float>& direction) noexcept;
  void ResetPosition() noexcept;
  // Setters
  void SetPosition(const Vector<float>& position) noexcept;
  // Getters
  glm::mat4x4* GetOrthoMatrix() noexcept;
  glm::mat4x4* GetViewMatrix() noexcept;
  glm::mat4x4* GetViewOrthoMatrix() noexcept;
};
#endif  // CAMERA_HPP_