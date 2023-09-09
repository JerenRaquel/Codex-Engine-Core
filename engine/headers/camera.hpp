#ifndef CAMERA_HPP_
#define CAMERA_HPP_

// Std
#include <string>
// Libs
#include "mat4x4.hpp"
#include "gtc/matrix_transform.hpp"
// Engine
#include "util/vector3.hpp"
#include "engine.hpp"

class Camera {
 private:
  Vector2<int> windowSize_;
  glm::mat4x4* orthoMatrix_ = nullptr;
  glm::mat4x4* originalViewMatrix_ = nullptr;
  glm::mat4x4* viewMatrix_ = nullptr;
  glm::mat4x4* orthoViewMatrix_ = nullptr;
  Vector3<float> position_;
  float cameraSpeed_ = 5.0f;
  float near_;
  float far_;
  bool isOrthoDirty_ = true;
  bool isViewDirty_ = true;
  bool isOrthoViewDirty_ = true;
  InputSystem* inputSystem_ = nullptr;
  std::string onDirectionUpdateUUID_;
  std::string onKeyPressUUID_;

 public:
  Camera(Vector2<int> windowSize, float near, float far,
         InputSystem* inputSystem);
  ~Camera();

  // Utility
  void UpdatePosition(const Vector2<float>& direction) noexcept;
  void ResetPosition() noexcept;
  // Setters
  void SetPosition(const Vector2<float>& position) noexcept;
  void SetPosition(const float& x, const float& y, const float& z) noexcept;
  // Getters
  glm::mat4x4* GetOrthoMatrix() noexcept;
  glm::mat4x4* GetViewMatrix() noexcept;
  glm::mat4x4* GetOriginalViewMatrix() noexcept;
  glm::mat4x4* GetViewOrthoMatrix() noexcept;
};
#endif  // CAMERA_HPP_