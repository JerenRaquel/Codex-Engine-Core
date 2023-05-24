#include "../headers/drone.hpp"

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

Mesh* const Drone::GetMesh() const noexcept { return this->mesh_; }
