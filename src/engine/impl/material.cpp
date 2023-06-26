#include "material.hpp"

Material::Material()
    : Material("default", Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f, nullptr) {}

Material::Material(const std::string& shaderName)
    : Material(shaderName, Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f, nullptr) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color)
    : Material(shaderName, color, 1.0f, nullptr) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color,
                   const float& alpha)
    : Material(shaderName, color, alpha, nullptr) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color,
                   const float& alpha, Texture* texture) {
  this->shaderName_ = shaderName;
  this->texture_ = texture;
  this->color_ = color;
  this->alpha_ = alpha;
}

Material::~Material() {
  if (this->texture_ != nullptr) {
    delete this->texture_;
  }
}

// Utility
Material* Material::RandomizeColor() noexcept {
  this->color_ = GenerateRandomColor();
  return this;
}

const bool Material::BindTexture() noexcept {
  if (this->texture_ != nullptr) {
    this->texture_->Bind();
    return true;
  }
  return false;
}

void Material::UnbindTexture() noexcept {
  if (this->texture_ != nullptr) {
    this->texture_->Unbind();
  }
}

Material* Material::ToggleBackgroundColor() noexcept {
  if (this->texture_ != nullptr) {
    this->enableBackgroundColor_ = !this->enableBackgroundColor_;
  }
  return this;
}

// Setters
Material* Material::SetShaderName(const std::string& shaderName) noexcept {
  this->shaderName_ = shaderName;
  return this;
}

Material* Material::SetColor(const Vector3<float>& color) noexcept {
  return this->SetColor(color.x, color.y, color.z);
}

Material* Material::SetColor(const Vector3<float>& color,
                             const float& alpha) noexcept {
  return this->SetColor(color.x, color.y, color.z, alpha);
}

Material* Material::SetColor(const float& r, const float& g,
                             const float& b) noexcept {
  this->color_.x = r;
  this->color_.y = g;
  this->color_.z = b;
  return this;
}

Material* Material::SetColor(const float& r, const float& g, const float& b,
                             const float& alpha) noexcept {
  this->color_.x = r;
  this->color_.y = g;
  this->color_.z = b;
  this->alpha_ = alpha;
  return this;
}

Material* Material::SetAlpha(const float& alpha) noexcept {
  this->alpha_ = alpha;
  return this;
}

Material* Material::SetTexture(Texture* texture) noexcept {
  this->texture_ = texture;
  return this;
}

// Getters
const std::string& Material::GetShaderName() const noexcept {
  return this->shaderName_;
}

const Vector3<float>& Material::GetColor() const noexcept {
  return this->color_;
}

const float& Material::GetAlpha() const noexcept { return this->alpha_; }

const bool& Material::GetBackgroundTextureState() const noexcept {
  return this->enableBackgroundColor_;
}
