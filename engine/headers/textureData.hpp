#ifndef TEXTUREDATA_HPP_
#define TEXTUREDATA_HPP_

// Engine
#include "texture.hpp"
#include "shaders/shader.hpp"

class TextureData {
 private:
  Texture* texture_;
  int cellWidthAmount_;
  int cellHeightAmount_;
  int maxTextureIndex_;
  bool isTransparent_ = false;

 public:
  TextureData(Texture* texture);
  TextureData(Texture* texture, const int cellWidthAmount,
              const int cellHeightAmount);
  ~TextureData();

  // Utility
  const TextureData* Bind(const Shader* const shader,
                          const int& textureIndex) const noexcept;
  const TextureData* Unbind() const noexcept;
  const TextureData* ToggleTextureTransparency() noexcept;
};
#endif  // TEXTUREDATA_HPP_