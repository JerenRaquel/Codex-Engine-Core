#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

// Std
#include <string>
// Engine
#include "util/vector3.hpp"
#include "util/helpers.hpp"
#include "texture.hpp"

class Material {
 private:
  std::string shaderName_;
  Texture* texture_;
  Vector3<float> color_;
  float alpha_;
  bool enableBackgroundColor_ = false;

 public:
  Material();
  Material(const std::string& shaderName);
  Material(const std::string& shaderName, const Vector3<float>& color);
  Material(const std::string& shaderName, const Vector3<float>& color,
           const float& alpha);
  Material(const std::string& shaderName, const Vector3<float>& color,
           const float& alpha, Texture* texture);
  ~Material();

  // Utility
  Material* RandomizeColor() noexcept;
  const bool BindTexture() noexcept;
  void UnbindTexture() noexcept;
  Material* ToggleBackgroundColor() noexcept;

  // Setters
  Material* SetShaderName(const std::string& shaderName) noexcept;
  Material* SetColor(const Vector3<float>& color) noexcept;
  Material* SetColor(const Vector3<float>& color, const float& alpha) noexcept;
  Material* SetColor(const float& r, const float& g, const float& b) noexcept;
  Material* SetColor(const float& r, const float& g, const float& b,
                     const float& alpha) noexcept;
  Material* SetAlpha(const float& alpha) noexcept;
  Material* SetTexture(Texture* texture) noexcept;

  // Getters
  const std::string& GetShaderName() const noexcept;
  const Vector3<float>& GetColor() const noexcept;
  const float& GetAlpha() const noexcept;
  const bool& GetBackgroundTextureState() const noexcept;
};
#endif  // MATERIAL_HPP_