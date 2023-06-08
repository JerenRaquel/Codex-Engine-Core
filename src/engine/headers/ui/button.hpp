#ifndef BUTTON_HPP_
#define BUTTON_HPP_

// Std
#include <string>
// Engine
#include "util/vector.hpp"
#include "mesh.hpp"
#include "material.hpp"
#include "transform.hpp"
#include "textHandler.hpp"
#include "engine.hpp"
#include "renderData.hpp"

class Button {
 private:
  void (*callback_)(const Engine* const engine,
                    const Button* const self) = nullptr;

  //* Mesh Data
  MeshRenderData* meshRenderData_ = nullptr;  // Freed in Scene Class
  TextRenderData* textRenderData_ = nullptr;  // Freed in Scene Class
  Transform* transform_;
  Material* material_;

 public:
  Button(const Vector<float>& position, const Vector<float>& scale,
         void (*callback)(const Engine* const engine,
                          const Button* const self));
  Button(const Vector<float>& position, const std::string& text,
         void (*callback)(const Engine* const engine,
                          const Button* const self));
  ~Button();

  // Utility
  void InvokeCallback(const Engine* const engine) const noexcept;
  bool IsHovered(const Vector<float>& mousePosition) noexcept;

  // Setters
  const Button* const SetAlpha(const float& alpha) noexcept;
  const Button* const SetColor(const Vector3<float>& color) noexcept;
  const Button* const SetColor(const float& r, const float& g,
                               const float& b) noexcept;
  const Button* const SetTextColor(const Vector3<float>& color) const noexcept;
  const Button* const SetTextColor(const float& r, const float& g,
                                   const float& b) const noexcept;

  // Getters
  const std::string GetName() const noexcept;
  const Vector<int> GetNamePosition() const noexcept;
  Transform* const GetTransform() const noexcept;
  Material* const GetMaterial() const noexcept;
  MeshRenderData* const GetMeshRenderData() const noexcept;
  TextRenderData* const GetTextRenderData() const noexcept;
};
#endif  // BUTTON_HPP_