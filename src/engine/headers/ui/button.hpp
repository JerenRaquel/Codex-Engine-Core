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
  unsigned int ticks_ = 10;
  void (*callback_)(Engine* const engine, Button* const self) = nullptr;
  void* metaData_ = nullptr;
  void (*metaDataDestructor_)(void* const metaData) = nullptr;

  //* Mesh Data
  MeshRenderData* meshRenderData_ = nullptr;  // Freed in Scene Class
  TextRenderData* textRenderData_ = nullptr;  // Freed in Scene Class
  Transform* transform_;
  Material* material_;

 public:
  Button(const Vector<float>& position, const Vector<float>& scale,
         void (*callback)(Engine* const engine, Button* const self));
  Button(const Vector<float>& position, const Vector<float>& scale,
         void (*callback)(Engine* const engine, Button* const self),
         const std::string& text, const Engine* const engine);
  ~Button();

  // Utility
  void InvokeCallback(Engine* const engine) noexcept;
  bool IsHovered(const Vector<float>& mousePosition) noexcept;

  // Setters
  Button* const SetAlpha(const float& alpha) noexcept;
  Button* const SetColor(const Vector3<float>& color) noexcept;
  Button* const SetColor(const float& r, const float& g,
                         const float& b) noexcept;
  Button* const SetTextColor(const Vector3<float>& color) noexcept;
  Button* const SetTextColor(const float& r, const float& g,
                             const float& b) noexcept;
  Button* const SetMetaData(
      void* const metaData,
      void (*metaDataDestructor)(void* const metaData)) noexcept;

  // Getters
  const std::string GetName() const noexcept;
  const Vector<int> GetNamePosition() const noexcept;
  Transform* const GetTransform() const noexcept;
  Material* const GetMaterial() const noexcept;
  MeshRenderData* const GetMeshRenderData() const noexcept;
  TextRenderData* const GetTextRenderData() const noexcept;
  void* const GetMetaData() const noexcept;
};
#endif  // BUTTON_HPP_