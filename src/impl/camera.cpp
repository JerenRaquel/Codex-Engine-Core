#include "../headers/camera.hpp"

Camera::Camera(Vector<int> windowSize) {
  this->windowSize_ = windowSize;
  this->position_ = Vector3<float>(0.0f, 0.0f, 0.0f);
  this->target_ = Vector3<float>(0.0f, 0.0f, 0.0f);
  this->up_ = Vector3<float>(0.0f, 1.0f, 0.0f);
  this->isDirty_ = true;
  this->Recalculate();
}

Camera::~Camera() {}

void Camera::Recalculate() noexcept {
  if (!this->isDirty_) return;

  this->viewMatrix_ = glm::lookAt(this->position_.ToGLM(),
                                  this->target_.ToGLM(), this->up_.ToGLM());
  this->orthoMatrix_ =
      glm::ortho(0.0f, static_cast<float>(this->windowSize_.x), 0.0f,
                 static_cast<float>(this->windowSize_.y), -1.0f, 1.0f);

  this->isDirty_ = false;
}

float* Camera::GetOrthoMatrix() const noexcept {
  const float* temp = glm::value_ptr(this->orthoMatrix_);
  float* result = new float[16];
  for (int i = 0; i < 16; i++) {
    result[i] = temp[i];
  }
  return result;
}

float* Camera::GetViewMatrix() const noexcept {
  const float* temp = glm::value_ptr(this->viewMatrix_);
  float* result = new float[16];
  for (int i = 0; i < 16; i++) {
    result[i] = temp[i];
  }
  return result;
}