#ifndef BUTTON_HPP_
#define BUTTON_HPP_

// Std
#include <string>
// Engine
#include "vector.hpp"
#include "mesh.hpp"
#include "material.hpp"
#include "transform.hpp"
#include "textHandler.hpp"
#include "engine.hpp"

class Button {
 private:
  void (*callback_)(const Engine* const engine) = nullptr;
  std::string name_ = "";
  Vector<int> namePosition_;

  //* Mesh Data
  Transform* transform_;
  Material* material_;

 public:
  Button(const Vector<float>& position, const Vector<float>& scale,
         void (*callback)(const Engine* const engine));
  Button(const Vector<float>& position, const std::string& text,
         void (*callback)(const Engine* const engine));
  ~Button();

  // Utility
  void InvokeCallback(const Engine* const engine) const noexcept;
  bool IsHovered(const Vector<float>& mousePosition) noexcept;

  // Setters
  Button* SetAlpha(const float& alpha) noexcept;
  Button* SetColor(const Vector3<float>& color) noexcept;
  Button* SetColor(const float& r, const float& g, const float& b) noexcept;

  // Getters
  const std::string& GetName() const noexcept;
  const Vector<int>& GetNamePosition() const noexcept;
  Transform* const GetTransform() const noexcept;
  Material* const GetMaterial() const noexcept;
};
#endif  // BUTTON_HPP_