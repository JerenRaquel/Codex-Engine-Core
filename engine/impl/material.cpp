#include "material.hpp"

Material::Material()
    : Material("default", Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f, nullptr) {}

Material::Material(const std::string& shaderName)
    : Material(shaderName, Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f, nullptr, 0) {
}

Material::Material(const std::string& shaderName, const Vector3<float>& color)
    : Material(shaderName, color, 1.0f, nullptr, 0) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color,
                   const float& alpha)
    : Material(shaderName, color, alpha, nullptr, 0) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color,
                   const float& alpha, TextureData* textureData)
    : Material(shaderName, color, alpha, textureData, 0) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color,
                   const float& alpha, TextureData* textureData,
                   const int& textureDataIndex) {
  this->shaderName_ = shaderName;
  this->textureData_ = textureData;
  this->textureDataIndex_ = textureDataIndex;
  this->color_ = color;
  this->alpha_ = alpha;
}

Material::~Material() { delete this->textureData_; }

// Utility
Material* Material::RandomizeColor() noexcept {
  this->color_ = GenerateRandomColor();
  return this;
}

Material* Material::BindTextureData(const Shader* const shader) noexcept {
  if (this->textureData_ != nullptr) {
    this->textureData_->Bind(shader, this->textureDataIndex_);
    shader->PassUniformBool("useTexture", true);
  } else {
    shader->PassUniformBool("useTexture", false);
    shader->PassUniformBool("useBackgroundColor", false);
  }

  return this;
}

Material* Material::UnbindTextureData() noexcept {
  if (this->textureData_ != nullptr) {
    this->textureData_->Unbind();
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

Material* Material::SetTextureData(TextureData* textureData) noexcept {
  this->textureData_ = textureData;
  return this;
}

Material* Material::SetTextureDataIndex(const int& textureDataIndex) noexcept {
  this->textureDataIndex_ = textureDataIndex;
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
