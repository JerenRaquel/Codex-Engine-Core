#ifndef TEXTUREDATA_HPP_
#define TEXTUREDATA_HPP_

// Engine
#include "texture.hpp"
#include "shaders/shader.hpp"
// Std
#include <memory>

class TextureData {
 private:
  std::shared_ptr<Texture> texture_;
  int cellWidthAmount_;
  int cellHeightAmount_;
  int maxTextureIndex_;
  bool isTransparent_ = false;

 public:
  TextureData(std::shared_ptr<Texture> texture);
  TextureData(std::shared_ptr<Texture> texture, const int cellWidthAmount,
              const int cellHeightAmount);
  ~TextureData();

  // Utility
  const TextureData* Bind(const Shader* const shader,
                          const int& textureIndex) const noexcept;
  const TextureData* Unbind() const noexcept;
  const TextureData* ToggleTextureTransparency() noexcept;
};
#endif  // TEXTUREDATA_HPP_