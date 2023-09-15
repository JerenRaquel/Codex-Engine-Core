#include "material.hpp"

Material::Material()
    : Material("default", Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f, "", 0) {}

Material::Material(const std::string& shaderName)
    : Material(shaderName, Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f, "", 0) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color)
    : Material(shaderName, color, 1.0f, "", 0) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color,
                   const float& alpha)
    : Material(shaderName, color, alpha, "", 0) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color,
                   const float& alpha, const std::string& textureName)
    : Material(shaderName, color, alpha, textureName, 0) {}

Material::Material(const std::string& shaderName, const Vector3<float>& color,
                   const float& alpha, const std::string& textureName,
                   const int& textureDataIndex) {
  this->shaderName_ = shaderName;
  this->textureName_ = textureName;
  this->textureDataIndex_ = textureDataIndex;
  this->color_ = color;
  this->alpha_ = alpha;
}

Material::~Material() {}

// Utility
Material* Material::RandomizeColor() noexcept {
  this->color_ = GenerateRandomColor();
  return this;
}

Material* Material::BindTextureData(
    const Shader* const shader, const TextureData* const textureData) noexcept {
  textureData->texture->Bind();
  shader->PassUniformBool("useTexture", true);
  shader->PassUniformBool("useBackgroundColor", this->isTransparent_);
  shader->PassUniform3i(
      "uvInfo",
      Vector3<int>(textureData->cellSizeX, textureData->cellSizeY,
                   this->textureDataIndex_ < textureData->maxTextureIndex
                       ? this->textureDataIndex_
                       : 0));

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

Material* Material::SetTextureName(const std::string& textureName) noexcept {
  this->textureName_ = textureName;
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

const std::string& Material::GetTextureName() const noexcept {
  return this->textureName_;
}

const Vector3<float>& Material::GetColor() const noexcept {
  return this->color_;
}

const float& Material::GetAlpha() const noexcept { return this->alpha_; }
