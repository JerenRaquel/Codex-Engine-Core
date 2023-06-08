#include "ui/button.hpp"

Button::Button(const Vector<float>& position, const Vector<float>& scale,
               void (*callback)(const Engine* const engine)) {
  this->callback_ = callback;
  this->material_ =
      new Material("button", Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f);
  this->transform_ = new Transform(position, scale);
}

Button::Button(const Vector<float>& position, const std::string& text,
               void (*callback)(const Engine* const engine)) {
  this->name_ = text;
  this->callback_ = callback;
  this->material_ =
      new Material("button", Vector3<float>(0.5f, 0.5f, 0.5f), 1.0f);
  float width = (text.length() * TextHandler_MaxWidth_) / 2.0f;
  float height = (TextHandler_MaxHeight_ + 20) / 2.0f;
  Vector<float> scale(width, height);
  this->transform_ = new Transform(position, scale);
  Vector<float> namePos = position - scale;
  this->namePosition_ = Vector<int>(namePos.x + 40, namePos.y + 10);
}

Button::~Button() {
  delete this->transform_;
  delete this->material_;
}

// Utility
void Button::InvokeCallback(const Engine* const engine) const noexcept {
  this->callback_(engine);
}

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

const Vector<int>& Button::GetNamePosition() const noexcept {
  return this->namePosition_;
}

Transform* const Button::GetTransform() const noexcept {
  return this->transform_;
}

Material* const Button::GetMaterial() const noexcept { return this->material_; }
