#include "../headers/camera.hpp"

Camera::Camera(Vector<int> windowSize, float near, float far,
               InputSystem* inputSystem) {
  this->windowSize_ = windowSize;
  this->near_ = near;
  this->far_ = far;
  this->position_ = Vector3<float>(0.0f, 0.0f, -1.0f);
  this->orthoMatrix_ = new glm::mat4x4();
  this->originalViewMatrix_ = new glm::mat4x4();
  this->viewMatrix_ = new glm::mat4x4();
  this->orthoViewMatrix_ = new glm::mat4x4();
  this->inputSystem_ = inputSystem;

  *(this->originalViewMatrix_) = *(this->GetViewMatrix());

  this->onDirectionUpdateUUID_ = this->inputSystem_->AssignOnDirectionUpdate(
      {reinterpret_cast<void*>(this),
       [](void* camera, const Vector<float>& direction) {
         Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
         cameraPtr->UpdatePosition(direction * -1);
       }});
  this->onKeyPressUUID_ = this->inputSystem_->AssignOnKeyPress(
      GLFW_KEY_R, {reinterpret_cast<void*>(this), [](void* camera) {
                     Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
                     cameraPtr->ResetPosition();
                   }});
}

Camera::~Camera() {
  delete this->orthoMatrix_;
  delete this->originalViewMatrix_;
  delete this->viewMatrix_;
  delete this->orthoViewMatrix_;
  this->inputSystem_->UnassignOnDirectionUpdate(this->onDirectionUpdateUUID_);
  this->inputSystem_->UnassignOnKeyPress(GLFW_KEY_R, this->onKeyPressUUID_);
}

void Camera::UpdatePosition(const Vector<float>& direction) noexcept {
  this->position_.x += direction.x * this->cameraSpeed_;
  this->position_.y += direction.y * this->cameraSpeed_;

  this->isViewDirty_ = true;
}

void Camera::ResetPosition() noexcept {
  this->SetPosition(Vector3<float>(0.0f, 0.0f, -1.0f));
}

void Camera::SetPosition(const Vector<float>& position) noexcept {
  this->position_ = position;
  this->isViewDirty_ = true;
}

void Camera::SetPosition(const float& x, const float& y,
                         const float& z) noexcept {
  this->SetPosition(Vector3<float>(x, y, z));
}

glm::mat4x4* Camera::GetOrthoMatrix() noexcept {
  if (this->isOrthoDirty_) {
    *(this->orthoMatrix_) = glm::ortho(
        0.0f, static_cast<float>(this->windowSize_.x), 0.0f,
        static_cast<float>(this->windowSize_.y), this->near_, this->far_);

    this->isOrthoDirty_ = false;
    this->isOrthoViewDirty_ = true;
  }

  return this->orthoMatrix_;
}

glm::mat4x4* Camera::GetViewMatrix() noexcept {
  if (this->isViewDirty_) {
    *(this->viewMatrix_) =
        glm::translate(glm::mat4x4(1.0f), this->position_.ToGLMVec3f());

    this->isViewDirty_ = false;
    this->isOrthoViewDirty_ = true;
  }

  return this->viewMatrix_;
}

glm::mat4x4* Camera::GetOriginalViewMatrix() noexcept {
  return this->originalViewMatrix_;
}

glm::mat4x4* Camera::GetViewOrthoMatrix() noexcept {
  if (this->isOrthoViewDirty_ || this->isViewDirty_ || this->isOrthoDirty_) {
    *(this->orthoViewMatrix_) =
        (*(this->GetOrthoMatrix())) * (*(this->GetViewMatrix()));

    this->isOrthoViewDirty_ = false;
  }

  return this->orthoViewMatrix_;
}