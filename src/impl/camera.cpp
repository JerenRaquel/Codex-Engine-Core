#include "../headers/camera.hpp"

Camera::Camera(Vector<int> windowSize) {
  this->windowSize_ = windowSize;
  this->position_ = Vector3<float>(0.0f, 0.0f, 0.0f);
  this->target_ = Vector3<float>(0.0f, 0.0f, 0.0f);
  this->up_ = Vector3<float>(0.0f, 1.0f, 0.0f);
  this->isDirty_ = true;
  this->orthoMatrix_ = new glm::mat4x4();
  this->viewMatrix_ = new glm::mat4x4();

  this->Recalculate();
}

Camera::~Camera() {
  delete this->orthoMatrix_;
  delete this->viewMatrix_;
}

void Camera::Recalculate() noexcept {
  if (!this->isDirty_) return;

  glm::mat4x4 viewTemp = glm::lookAt(this->position_.ToGLM(),
                                     this->target_.ToGLM(), this->up_.ToGLM());
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      (*(this->viewMatrix_))[i][j] = viewTemp[i][j];
    }
  }

  glm::mat4x4 orthoTemp =
      glm::ortho(0.0f, static_cast<float>(this->windowSize_.x), 0.0f,
                 static_cast<float>(this->windowSize_.y), -1.0f, 1.0f);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      (*(this->orthoMatrix_))[i][j] = orthoTemp[i][j];
    }
  }

  this->isDirty_ = false;
}

glm::mat4x4* Camera::GetOrthoMatrix() const noexcept {
  return this->orthoMatrix_;
}

glm::mat4x4* Camera::GetViewMatrix() const noexcept {
  return this->viewMatrix_;
}