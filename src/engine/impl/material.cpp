#include "material.hpp"

Material::Material() : Material("default", Vector3<float>(1.0f, 1.0f, 1.0f)) {}

Material::Material(const std::string& shaderName)
    : Material(shaderName, Vector3<float>(1.0f, 1.0f, 1.0f)) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color)
    : shaderName_(shaderName), color_(color) {}

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

Material* Material::SetColor(const float& r, const float& g,
                             const float& b) noexcept {
  this->color_.x = r;
  this->color_.y = g;
  this->color_.z = b;
  return this;
}

// Getters
const std::string& Material::GetShaderName() const noexcept {
  return this->shaderName_;
}

const Vector3<float>& Material::GetColor() const noexcept {
  return this->color_;
}
