#include "ui/button.hpp"

void Button::SetupMeshData(const Vector<float>& position,
                           const Vector<float>& scale) noexcept {
  this->material_ =
      new Material("button", Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f);
  this->transform_ = new Transform(position, scale);
}

Button::Button(const Vector<float>& position, void (*callback)(void),
               const Vector<float>& scale) {
  this->callback_ = callback;
  this->SetupMeshData(position, scale);
}

Button::Button(const Vector<float>& position, void (*callback)(void),
               const std::string& text) {
  this->name_ = text;
  this->callback_ = callback;
  // TODO: Implement something better?
  this->SetupMeshData(position, Vector<float>(text.length() * 0.5f, 1.0f));
}

Button::~Button() {
  delete this->transform_;
  delete this->material_;
}

// Utility
void Button::InvokeCallback() const noexcept { this->callback_(); }

bool Button::IsHovered(const Vector<float>& mousePosition) noexcept {
  Vector<float> scale = this->transform_->GetScale();
  if (mousePosition.IsWithinRectDistance(this->transform_->GetPosition(),
                                         scale.x, scale.y)) {
    this->SetAlpha(0.5f);
    return true;
  }
  this->SetAlpha(1.0f);
  return false;
}

// Setters
Button* Button::SetAlpha(const float& alpha) noexcept {
  this->material_->SetAlpha(alpha);
  return this;
}

Button* Button::SetColor(const Vector3<float>& color) noexcept {
  return this->SetColor(color.x, color.y, color.z);
}

Button* Button::SetColor(const float& r, const float& g,
                         const float& b) noexcept {
  this->material_->SetColor(r, g, b);
  return this;
}

// Getters
const std::string& Button::GetName() const noexcept { return this->name_; }

Transform* const Button::GetTransform() const noexcept {
  return this->transform_;
}

Material* const Button::GetMaterial() const noexcept { return this->material_; }
