#include "../headers/camera.hpp"

Camera::Camera(Vector<int> windowSize, float near, float far) {
  this->windowSize_ = windowSize;
  this->near_ = near;
  this->far_ = far;
  this->position_ = Vector3<float>(0.0f, 0.0f, -1.0f);
  this->orthoMatrix_ = new glm::mat4x4();
  this->viewMatrix_ = new glm::mat4x4();
  this->orthoViewMatrix_ = new glm::mat4x4();
}

Camera::~Camera() {
  delete this->orthoMatrix_;
  delete this->viewMatrix_;
  delete this->orthoViewMatrix_;
}

void Camera::UpdatePosition(const Vector<float>& direction) noexcept {
  this->position_.x += direction.x * this->cameraSpeed_;
  this->position_.y += direction.y * this->cameraSpeed_;

  this->isViewDirty_ = true;
}

void Camera::ResetPosition() noexcept {
  this->position_ = Vector3<float>(0.0f, 0.0f, -1.0f);
  this->isViewDirty_ = true;
}

void Camera::SetPosition(const Vector<float>& position) noexcept {
  this->position_ = position;
  this->isViewDirty_ = true;
}

glm::mat4x4* Camera::GetOrthoMatrix() noexcept {
  if (this->isOrthoDirty_) {
    glm::mat4x4 orthoTemp = glm::ortho(
        0.0f, static_cast<float>(this->windowSize_.x), 0.0f,
        static_cast<float>(this->windowSize_.y), this->near_, this->far_);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        (*(this->orthoMatrix_))[i][j] = orthoTemp[i][j];
      }
    }
    this->isOrthoDirty_ = false;
    this->isOrthoViewDirty_ = true;
  }

  return this->orthoMatrix_;
}

glm::mat4x4* Camera::GetViewMatrix() noexcept {
  if (this->isViewDirty_) {
    glm::mat4x4 viewTemp =
        glm::translate(glm::mat4x4(1.0f), this->position_.ToGLMVec3f());
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        (*(this->viewMatrix_))[i][j] = viewTemp[i][j];
      }
    }

    this->isViewDirty_ = false;
    this->isOrthoViewDirty_ = true;
  }

  return this->viewMatrix_;
}

glm::mat4x4* Camera::GetViewOrthoMatrix() noexcept {
  if (this->isOrthoViewDirty_ || this->isViewDirty_ || this->isOrthoDirty_) {
    glm::mat4x4 viewOrthoTemp =
        (*(this->GetOrthoMatrix())) * (*(this->GetViewMatrix()));
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        (*(this->orthoViewMatrix_))[i][j] = viewOrthoTemp[i][j];
      }
    }

    this->isOrthoViewDirty_ = false;
  }

  return this->orthoViewMatrix_;
}