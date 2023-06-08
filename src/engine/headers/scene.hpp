#ifndef SCENE_HPP_
#define SCENE_HPP_

class Button;

// Std
#include <vector>
// Engine
#include "renderData.hpp"
#include "ui/button.hpp"

class Scene {
 private:
  //* Data - All Data Freed Here
  // Render Data
  std::vector<MeshRenderData*>* meshRenderDataPointer_;
  std::vector<TextRenderData*>* textRenderDataPointer_;

  // UI
  std::vector<Button*>* buttons_;

  // Actions
  std::vector<Action*>* actions_;

 public:
  Scene();
  ~Scene();

  // Utility
  void Start(Engine* const engine) const noexcept;
  void Update(Engine* const engine) const noexcept;
  const Scene* const AddMeshRenderData(
      MeshRenderData* meshRenderData) const noexcept;
  const Scene* const AddTextRenderData(
      TextRenderData* textRenderData) const noexcept;
  const Scene* const AddButton(Button* button) const noexcept;
  const Scene* const AddAction(Action* action) const noexcept;

  // Getters
  std::vector<MeshRenderData*>* const GetMeshRenderDataPointer() const noexcept;
  std::vector<TextRenderData*>* const GetTextRenderDataPointer() const noexcept;
};
#endif  // SCENE_HPP_