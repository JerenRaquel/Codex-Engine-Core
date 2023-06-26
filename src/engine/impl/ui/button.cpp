#include "ui/button.hpp"

void Button::SetUp(const Vector<float>& position, const Vector<float>& scale,
                   Texture* texture, const std::string& text,
                   Vector<float>* textSize) noexcept {
  this->transform_ = new Transform(position, scale);

  if (texture != nullptr) {
    this->material_ =
        new Material("button", Vector3<float>(0.5f, 0.5f, 0.5f), 1.0f, texture);
  } else {
    this->material_ =
        new Material("button", Vector3<float>(0.5f, 0.5f, 0.5f), 1.0f);
  }

  this->meshRenderData_ =
      new MeshRenderData("Quad", this->material_, this->transform_);

  if (text != "") {
    Vector<float> namePos = position - *textSize / 2.0f;
    this->textRenderData_ =
        new TextRenderData(text, Vector<int>(namePos.x, namePos.y),
                           Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f);
  }
}

Button::Button(const Vector<float>& position, const Vector<float>& scale,
               void (*callback)(Engine* const engine, Button* const self)) {
  this->callback_ = callback;
  this->SetUp(position, scale, nullptr, "", nullptr);
}

Button::Button(const Vector<float>& position, const Vector<float>& scale,
               void (*callback)(Engine* const engine, Button* const self),
               const std::string& text, const Engine* const engine) {
  this->callback_ = callback;
  Vector<float> textSize = engine->GetRenderer()->GetTextSize(text, 1.0f);
  this->SetUp(position, scale, nullptr, text, &textSize);
}

Button::Button(const Vector<float>& position, const Vector<float>& scale,
               void (*callback)(Engine* const engine, Button* const self),
               Texture* texture) {
  this->callback_ = callback;
  this->SetUp(position, scale, texture, "", nullptr);
}

Button::~Button() {
  delete this->transform_;
  delete this->material_;
  if (this->metaData_ != nullptr) {
    this->metaDataDestructor_(this->metaData_);
  }
}

// Utility
void Button::InvokeCallback(Engine* const engine) noexcept {
  if (this->ticks_ > 0) return;
  this->ticks_ = 10;
  if (this->callback_ == nullptr) {
    std::cout << "????" << std::endl;
    return;
  }
  this->callback_(engine, this);
}

bool Button::IsHovered(const Vector<float>& mousePosition) noexcept {
  if (this->ticks_ > 0) this->ticks_--;

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
Button* const Button::SetAlpha(const float& alpha) noexcept {
  this->material_->SetAlpha(alpha);
  return this;
}

Button* const Button::SetColor(const Vector3<float>& color) noexcept {
  return this->SetColor(color.x, color.y, color.z);
}

Button* const Button::SetColor(const float& r, const float& g,
                               const float& b) noexcept {
  this->material_->SetColor(r, g, b);
  return this;
}

Button* const Button::SetTextColor(const Vector3<float>& color) noexcept {
  if (this->textRenderData_ == nullptr) return this;

  this->textRenderData_->color_ = color;
  return this;
}

Button* const Button::SetTextColor(const float& r, const float& g,
                                   const float& b) noexcept {
  return this->SetTextColor(Vector3<float>(r, g, b));
}

Button* const Button::SetMetaData(
    void* const metaData,
    void (*metaDataDestructor)(void* const metaData)) noexcept {
  this->metaData_ = metaData;
  this->metaDataDestructor_ = metaDataDestructor;
  return this;
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

void* const Button::GetMetaData() const noexcept { return this->metaData_; }
