#ifndef SCENE_HPP_
#define SCENE_HPP_

class Button;
class Engine;

// Std
#include <vector>
#include <map>
#include <stack>
// Engine
#include "renderData.hpp"
#include "ui/button.hpp"

class Scene {
 private:
  //* Data - Most Data Freed Here
  // Meta Data
  Engine* engine_;                                      // Not Freed Here
  std::stack<std::string>* meshRenderDataUsedIDStack_;  // All Freed Here

  // Render Data
  std::map<std::string, MeshRenderData*>*
      meshRenderDataPointer_;                              // All Freed Here
  std::vector<MeshRenderData*>* meshUIRenderDataPointer_;  // All Freed Here
  std::vector<TextRenderData*>* textRenderDataPointer_;    // All Freed Here

  // UI
  std::vector<Button*>* buttons_;  // All Freed Here

  // Actions
  std::vector<Action*>* actions_;  // All Freed Here

 public:
  Scene(Engine* const engine);
  ~Scene();

  // Utility
  void Start() noexcept;
  void Update() const noexcept;
  void Finish() noexcept;
  const Scene* const AddMeshRenderData(
      std::string& id, MeshRenderData* meshRenderData) const noexcept;
  const Scene* const DestroyMeshRenderData(const std::string& id);
  const Scene* const AddMeshUIRenderData(
      MeshRenderData* meshRenderData) const noexcept;
  const Scene* const AddTextRenderData(
      TextRenderData* textRenderData) const noexcept;
  const Scene* const AddButton(Button* const button) const noexcept;
  const Scene* const AddAction(Action* action) noexcept;

  // Getters
  std::map<std::string, MeshRenderData*>* const GetMeshRenderDataPointer()
      const noexcept;
  std::vector<MeshRenderData*>* const GetMeshUIRenderDataPointer()
      const noexcept;
  std::vector<TextRenderData*>* const GetTextRenderDataPointer() const noexcept;
};
#endif  // SCENE_HPP_