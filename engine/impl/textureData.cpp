#include "textureData.hpp"

TextureData::TextureData(Texture* texture) : TextureData(texture, 1, 1) {}

TextureData::TextureData(Texture* texture, const int cellWidthAmount,
                         const int cellHeightAmount) {
  this->texture_ = texture;
  this->cellWidthAmount_ = cellWidthAmount;
  this->cellHeightAmount_ = cellHeightAmount;
  this->maxTextureIndex_ = cellWidthAmount * cellHeightAmount;
}

TextureData::~TextureData() { delete this->texture_; }

// Utility
const TextureData* TextureData::Bind(const Shader* const shader,
                                     const int& textureIndex) const noexcept {
  this->texture_->Bind();

  shader->PassUniformBool("useBackgroundColor", this->isTransparent_);
  shader->PassUniform3i(
      "uvInfo",
      Vector3<int>(this->cellWidthAmount_, this->cellHeightAmount_,
                   textureIndex < this->maxTextureIndex_ ? textureIndex : 0));

  return this;
}

const TextureData* TextureData::Unbind() const noexcept {
  this->texture_->Unbind();

  return this;
}

const TextureData* TextureData::ToggleTextureTransparency() noexcept {
  this->isTransparent_ = !this->isTransparent_;

  return this;
}
