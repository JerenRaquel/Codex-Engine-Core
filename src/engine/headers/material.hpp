#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

// Std
#include <string>
// Custom
#include "vector.hpp"
#include "helpers.hpp"

class Material {
 private:
  std::string shaderName_;
  Vector3<float> color_;

 public:
  Material();
  Material(const std::string& shaderName);
  Material(const std::string& shaderName, const Vector3<float>& color);
  ~Material();

  // Utility
  Material* RandomizeColor() noexcept;

  // Setters
  Material* SetShaderName(const std::string& shaderName) noexcept;
  Material* SetColor(const Vector3<float>& color) noexcept;
  Material* SetColor(const float& r, const float& g, const float& b) noexcept;

  // Getters
  const std::string& GetShaderName() const noexcept;
  const Vector3<float>& GetColor() const noexcept;
};
#endif  // MATERIAL_HPP_