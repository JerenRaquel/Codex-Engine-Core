#ifndef BUTTON_HPP_
#define BUTTON_HPP_

// Std
#include <string>
// Engine
#include "vector.hpp"
#include "mesh.hpp"
#include "material.hpp"
#include "transform.hpp"

class Button {
 private:
  void (*callback_)(void);
  std::string name_;

  //* Mesh Data
  Transform* transform_;
  Material* material_;

  void SetupMeshData(const Vector<float>& position,
                     const Vector<float>& scale) noexcept;

 public:
  Button(const Vector<float>& position, void (*callback)(void),
         const Vector<float>& scale);
  Button(const Vector<float>& position, void (*callback)(void),
         const std::string& text);
  ~Button();

  // Utility
  void InvokeCallback() const noexcept;
  bool IsHovered(const Vector<float>& mousePosition) noexcept;

  // Setters
  Button* SetAlpha(const float& alpha) noexcept;
  Button* SetColor(const Vector3<float>& color) noexcept;
  Button* SetColor(const float& r, const float& g, const float& b) noexcept;

  // Getters
  const std::string& GetName() const noexcept;
  Transform* const GetTransform() const noexcept;
  Material* const GetMaterial() const noexcept;
};
#endif  // BUTTON_HPP_