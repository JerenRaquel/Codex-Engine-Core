#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

// Std
#include <string>
// Engine
#include "util/vector3.hpp"
#include "util/helpers.hpp"
#include "texture.hpp"
#include "shaders/shader.hpp"

class Material {
 private:
  std::string shaderName_;
  Vector3<float> color_;
  float alpha_;
  // Texture Data
  std::string textureName_;
  int textureDataIndex_;
  bool isTransparent_ = false;

 public:
  Material();
  Material(const std::string& shaderName);
  Material(const std::string& shaderName, const Vector3<float>& color);
  Material(const std::string& shaderName, const Vector3<float>& color,
           const float& alpha);
  Material(const std::string& shaderName, const Vector3<float>& color,
           const float& alpha, const std::string& textureName);
  Material(const std::string& shaderName, const Vector3<float>& color,
           const float& alpha, const std::string& textureName,
            const int& textureDataIndex);
  ~Material();

  // Utility
  Material* RandomizeColor() noexcept;
  Material* BindTextureData(const Shader* const shader,
                            const TextureData* const textureData) noexcept;

  // Setters
  Material* SetShaderName(const std::string& shaderName) noexcept;
  Material* SetColor(const Vector3<float>& color) noexcept;
  Material* SetColor(const Vector3<float>& color, const float& alpha) noexcept;
  Material* SetColor(const float& r, const float& g, const float& b) noexcept;
  Material* SetColor(const float& r, const float& g, const float& b,
                     const float& alpha) noexcept;
  Material* SetAlpha(const float& alpha) noexcept;
  Material* SetTextureName(const std::string& textureName) noexcept;
  Material* SetTextureDataIndex(const int& textureDataIndex) noexcept;

  // Getters
  const std::string& GetShaderName() const noexcept;
  const std::string& GetTextureName() const noexcept;
  const Vector3<float>& GetColor() const noexcept;
  const float& GetAlpha() const noexcept;
};
#endif  // MATERIAL_HPP_