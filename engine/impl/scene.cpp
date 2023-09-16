#include "scene.hpp"

Scene::Scene(Engine* const engine) {
  this->engine_ = engine;
  this->meshRenderDataUsedIDStack_ = new std::stack<std::string>();
  this->meshRenderDataPointer_ = new std::map<std::string, MeshRenderData*>();
  this->meshUIRenderDataPointer_ = new std::vector<MeshRenderData*>();
  this->textRenderDataPointer_ = new std::vector<TextRenderData*>();
  this->buttons_ = new std::vector<Button*>();
  this->actions_ = new std::vector<Action*>();
}

Scene::~Scene() {
  delete this->meshRenderDataUsedIDStack_;

  for (auto data : *this->meshRenderDataPointer_) {
    delete data.second;
  }
  delete this->meshRenderDataPointer_;

  for (MeshRenderData* data : *this->meshUIRenderDataPointer_) {
    delete data;
  }
  delete this->meshUIRenderDataPointer_;

  for (TextRenderData* data : *this->textRenderDataPointer_) {
    delete data;
  }
  delete this->textRenderDataPointer_;

  for (Button* button : *this->buttons_) {
    delete button;
  }
  delete this->buttons_;

  for (Action* action : *(this->actions_)) {
    delete action;
  }
  delete this->actions_;
}

// Utility
void Scene::Start() noexcept {
  // Initilize actions
  for (unsigned int i = 0; i < this->actions_->size(); i++) {
    this->actions_->at(i)->OnStart(this->engine_);
  }
}

void Scene::Update() const noexcept {
  // Update actions
  for (unsigned int i = 0; i < this->actions_->size(); i++) {
    this->actions_->at(i)->OnUpdate(this->engine_);
  }

  // Update buttons
  InputSystem* inputSystem = this->engine_->GetInputSystem();
  for (unsigned int i = 0; i < this->buttons_->size(); i++) {
    Button* button = this->buttons_->at(i);
    if (button->IsHovered(inputSystem->GetMousePosition()) &&
        inputSystem->IsMouseDown()) {
      button->InvokeCallback(this->engine_);
      break;
    }
  }
}

void Scene::Finish() noexcept {
  // Finish actions
  for (unsigned int i = 0; i < this->actions_->size(); i++) {
    this->actions_->at(i)->OnFinish(this->engine_);
  }
}

const Scene* const Scene::AddMeshRenderData(
    std::string& id, MeshRenderData* meshRenderData) const noexcept {
  if (!this->meshRenderDataUsedIDStack_->empty()) {
    id = this->meshRenderDataUsedIDStack_->top();
    this->meshRenderDataUsedIDStack_->pop();
  } else {
    id = this->engine_->GenerateUUID();
  }
  this->meshRenderDataPointer_->insert(
      std::pair<std::string, MeshRenderData*>(id, meshRenderData));
  return this;
}

const Scene* const Scene::DestroyMeshRenderData(const std::string& id) {
  if (this->meshRenderDataPointer_->count(id) == 0) {
    throw std::runtime_error("MeshRenderData does not exist");
  }

  delete this->meshRenderDataPointer_->at(id);
  this->meshRenderDataPointer_->erase(id);
  this->meshRenderDataUsedIDStack_->push(id);

  return this;
}

const Scene* const Scene::AddMeshUIRenderData(
    MeshRenderData* meshRenderData) const noexcept {
  this->meshUIRenderDataPointer_->push_back(meshRenderData);
  return this;
}

const Scene* const Scene::AddTextRenderData(
    TextRenderData* textRenderData) const noexcept {
  this->textRenderDataPointer_->push_back(textRenderData);
  return this;
}

const Scene* const Scene::AddButton(Button* const button) const noexcept {
  this->buttons_->push_back(button);
  if (button->GetTextRenderData() != nullptr) {
    this->textRenderDataPointer_->push_back(button->GetTextRenderData());
  }
  this->meshUIRenderDataPointer_->push_back(button->GetMeshRenderData());

  return this;
}

const Scene* const Scene::AddAction(Action* action) noexcept {
  this->actions_->push_back(action);
  return this;
}

// Getters
std::vector<MeshRenderData*>* const Scene::GetMeshRenderDataPointer()
    const noexcept {
  std::vector<MeshRenderData*>* buffer = new std::vector<MeshRenderData*>();
  for (auto data : *this->meshRenderDataPointer_) {
    buffer->push_back(data.second);
  }
  return buffer;
}

std::vector<MeshRenderData*>* const Scene::GetMeshUIRenderDataPointer()
    const noexcept {
  return this->meshUIRenderDataPointer_;
}

std::vector<TextRenderData*>* const Scene::GetTextRenderDataPointer()
    const noexcept {
  return this->textRenderDataPointer_;
}
