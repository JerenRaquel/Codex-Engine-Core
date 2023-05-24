#include "../headers/drone.hpp"

Drone::Drone(Vector<float> position, Vector<float> scale)
    : Drone(position, scale, Vector3<float>(1.0f, 1.0f, 1.0f)) {}

Drone::Drone(Vector<float> position, Vector<float> scale,
             Vector3<float> color) {
  float vertices[] = {
      0.0f,  2.5f,  0.0f,  // top center
      -2.5f, -2.5f, 0.0f,  // bottom left
      2.5f,  -2.5f, 0.0f,  // bottom right
  };
  unsigned int indices[] = {
      0, 1, 2,  // first triangle
  };

  this->mesh_ = new Mesh(vertices, 9, indices, 3);
  this->mesh_->SetPosition(position)->SetScale(scale)->SetColor(color);
}

Drone::~Drone() {}

void Drone::OnStart(Engine* const engine, const std::string& tag,
                    const unsigned int id) const noexcept {
  if (this->startFunc_ != nullptr) {
    this->startFunc_(engine, const_cast<Drone* const>(this), tag, id);
  }
}

void Drone::OnUpdate(Engine* const engine, const std::string& tag,
                     const unsigned int id) const noexcept {
  if (this->updateFunc_ != nullptr) {
    this->updateFunc_(engine, const_cast<Drone* const>(this), tag, id);
  }
}

Drone* const Drone::AssignStartFunction(
    void (*func)(Engine* const engine, Drone* const self,
                 const std::string& tag, const unsigned int id)) noexcept {
  this->startFunc_ = func;
  return this;
}

Drone* const Drone::AssignUpdateFunction(
    void (*func)(Engine* const engine, Drone* const self,
                 const std::string& tag, const unsigned int id)) noexcept {
  this->updateFunc_ = func;
  return this;
}

Mesh* const Drone::GetMesh() const noexcept { return this->mesh_; }
