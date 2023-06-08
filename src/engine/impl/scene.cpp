#include "scene.hpp"

Scene::Scene() {
  this->meshRenderDataPointer_ = new std::vector<MeshRenderData*>();
  this->textRenderDataPointer_ = new std::vector<TextRenderData*>();
  this->buttons_ = new std::vector<Button*>();
  this->actions_ = new std::vector<Action*>();
}

Scene::~Scene() {
  for (MeshRenderData* data : *this->meshRenderDataPointer_) {
    delete data;
  }
  delete this->meshRenderDataPointer_;

  for (TextRenderData* data : *this->textRenderDataPointer_) {
    delete data;
  }
  delete this->textRenderDataPointer_;

  for (Button* button : *this->buttons_) {
    delete button;
  }
  delete this->buttons_;

  for (Action* action : *this->actions_) {
    delete action;
  }
  delete this->actions_;
}

// Utility

void Scene::Start(Engine* const engine) const noexcept {
  // Initilize actions
  for (unsigned int i = 0; i < this->actions_->size(); i++) {
    this->actions_->at(i)->OnStart(engine);
  }
}

void Scene::Update(Engine* const engine) const noexcept {
  // Update actions
  for (unsigned int i = 0; i < this->actions_->size(); i++) {
    this->actions_->at(i)->OnUpdate(engine);
  }

  // Update buttons
  InputSystem* inputSystem = engine->GetInputSystem();
  for (unsigned int i = 0; i < this->buttons_->size(); i++) {
    Button* button = this->buttons_->at(i);
    if (button->IsHovered(inputSystem->GetMousePosition()) &&
        inputSystem->IsMouseDown()) {
      button->InvokeCallback(engine);
      break;
    }
  }
}

const Scene* const Scene::AddMeshRenderData(
    MeshRenderData* meshRenderData) const noexcept {
  this->meshRenderDataPointer_->push_back(meshRenderData);
  return this;
}

const Scene* const Scene::AddTextRenderData(
    TextRenderData* textRenderData) const noexcept {
  this->textRenderDataPointer_->push_back(textRenderData);
  return this;
}

const Scene* const Scene::AddButton(Button* button) const noexcept {
  this->buttons_->push_back(button);
  this->textRenderDataPointer_->push_back(
      new TextRenderData(button->GetName(), button->GetNamePosition(),
                         Vector3<float>(1.0f, 1.0f, 1.0f), 1));
  this->meshRenderDataPointer_->push_back(new MeshRenderData(
      "Quad", button->GetMaterial(), button->GetTransform()));

  return this;
}

const Scene* const Scene::AddAction(Action* action) const noexcept {
  this->actions_->push_back(action);
  return this;
}

// Getters
std::vector<MeshRenderData*>* const Scene::GetMeshRenderDataPointer()
    const noexcept {
  return this->meshRenderDataPointer_;
}

std::vector<TextRenderData*>* const Scene::GetTextRenderDataPointer()
    const noexcept {
  return this->textRenderDataPointer_;
}
