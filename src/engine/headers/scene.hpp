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
  std::vector<MeshRenderData*>* meshRenderDataPointer_;  // All Freed Here
  std::vector<TextRenderData*>* textRenderDataPointer_;  // All Freed Here

  // UI
  std::vector<Button*>* buttons_;  // All Freed Here

  // Actions
  std::vector<Action*>* actions_;  // All Freed Here

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
  const Scene* const AddButton(Button* const button) const noexcept;
  const Scene* const AddAction(Action* action) const noexcept;

  // Getters
  std::vector<MeshRenderData*>* const GetMeshRenderDataPointer() const noexcept;
  std::vector<TextRenderData*>* const GetTextRenderDataPointer() const noexcept;
};
#endif  // SCENE_HPP_