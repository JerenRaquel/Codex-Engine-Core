#include "material.hpp"

Material::Material()
    : Material("default", Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f) {}

Material::Material(const std::string& shaderName)
    : Material(shaderName, Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color)
    : Material(shaderName, color, 1.0f) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color,
                   const float& alpha)
    : shaderName_(shaderName), color_(color), alpha_(alpha) {}

Material::~Material() {}

// Utility
Material* Material::RandomizeColor() noexcept {
  this->color_ = GenerateRandomColor();
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

// Getters
const std::string& Material::GetShaderName() const noexcept {
  return this->shaderName_;
}

const Vector3<float>& Material::GetColor() const noexcept {
  return this->color_;
}

const float& Material::GetAlpha() const noexcept { return this->alpha_; }

const bool Material::ShouldRender() const noexcept {
  return this->alpha_ > 0.0f;
}
