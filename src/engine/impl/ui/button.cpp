#include "ui/button.hpp"

Button::Button(const Vector<float>& position, const Vector<float>& scale,
               void (*callback)(const Engine* const engine,
                                const Button* const self)) {
  this->callback_ = callback;
  this->material_ =
      new Material("button", Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f);
  this->transform_ = new Transform(position, scale);

  this->meshRenderData_ =
      new MeshRenderData("Quad", this->material_, this->transform_);
}

Button::Button(const Vector<float>& position, const std::string& text,
               void (*callback)(const Engine* const engine,
                                const Button* const self)) {
  this->callback_ = callback;
  this->material_ =
      new Material("button", Vector3<float>(0.5f, 0.5f, 0.5f), 1.0f);

  float width = (text.length() * TextHandler_MaxWidth_) / 2.0f;
  float height = (TextHandler_MaxHeight_ + 20) / 2.0f;
  Vector<float> scale(width, height);
  this->transform_ = new Transform(position, scale);
  Vector<float> namePos = position - scale;

  this->meshRenderData_ =
      new MeshRenderData("Quad", this->material_, this->transform_);
  this->textRenderData_ =
      new TextRenderData(text, Vector<int>(namePos.x + 40, namePos.y + 10),
                         Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f);
}

Button::~Button() {
  delete this->transform_;
  delete this->material_;
}

// Utility
void Button::InvokeCallback(const Engine* const engine) const noexcept {
  this->callback_(engine, this);
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
const Button* const Button::SetAlpha(const float& alpha) noexcept {
  this->material_->SetAlpha(alpha);
  return this;
}

const Button* const Button::SetColor(const Vector3<float>& color) noexcept {
  return this->SetColor(color.x, color.y, color.z);
}

const Button* const Button::SetColor(const float& r, const float& g,
                                     const float& b) noexcept {
  this->material_->SetColor(r, g, b);
  return this;
}

const Button* const Button::SetTextColor(
    const Vector3<float>& color) const noexcept {
  if (this->textRenderData_ == nullptr) return this;

  this->textRenderData_->color_ = color;
  return this;
}

const Button* const Button::SetTextColor(const float& r, const float& g,
                                         const float& b) const noexcept {
  return this->SetTextColor(Vector3<float>(r, g, b));
}

// Getters
const std::string Button::GetName() const noexcept {
  if (this->textRenderData_ == nullptr) return "";
  return this->textRenderData_->GetText();
}

const Vector<int> Button::GetNamePosition() const noexcept {
  if (this->textRenderData_ == nullptr) return Vector<int>(0, 0);
  return this->textRenderData_->GetPosition();
}

Transform* const Button::GetTransform() const noexcept {
  return this->transform_;
}

Material* const Button::GetMaterial() const noexcept { return this->material_; }

MeshRenderData* const Button::GetMeshRenderData() const noexcept {
  return this->meshRenderData_;
}

TextRenderData* const Button::GetTextRenderData() const noexcept {
  return this->textRenderData_;
}
