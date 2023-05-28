#include "../headers/drone.hpp"

Drone::Drone(Vector<float>* position, Vector<float> scale)
    : Drone(position, scale, Vector3<float>(1.0f, 1.0f, 1.0f)) {}

Drone::Drone(Vector<float>* position, Vector<float> scale,
             Vector3<float> color) {
  float vertices[] = {
      0.0f,  2.5f,  0.0f,  // top center
      -2.5f, -2.5f, 0.0f,  // bottom left
      2.5f,  -2.5f, 0.0f,  // bottom right
  };
  unsigned int indices[] = {
      0, 1, 2,  // first triangle
  };

  this->position_ = position;
  this->mesh_ = new Mesh(vertices, 9, indices, 3, position);
  this->mesh_->SetScale(scale)->SetColor(color);
}

Drone::~Drone() {}

void Drone::OnStart(Engine* const engine, const std::string& tag,
                    const unsigned int id) noexcept {
  this->InternalStart(engine, tag, id);
}

void Drone::OnUpdate(Engine* const engine, const std::string& tag,
                     const unsigned int id) noexcept {
  this->InternalUpdate(engine, tag, id);
}

Mesh* const Drone::GetMesh() const noexcept { return this->mesh_; }

Vector<float>* const Drone::GetPosition() const noexcept {
  return this->position_;
}
