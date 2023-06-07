#include "../headers/drone.hpp"

Drone::Drone(Vector<float>* position, Vector<float> scale)
    : Drone(position, scale, Vector3<float>(1.0f, 1.0f, 1.0f)) {}

Drone::Drone(Vector<float>* position, Vector<float> scale,
             Vector3<float> color) {
  this->material_ = new Material();
  this->material_->SetColor(color);
  this->transform_ = new Transform(position, scale);
}

Drone::~Drone() {
  delete this->material_;
  delete this->transform_;
}

void Drone::OnUpdate(Engine* const engine, const std::string& tag,
                     const unsigned int id) noexcept {
  this->InternalUpdate(engine, tag, id);
}

Material* const Drone::GetMaterial() const noexcept { return this->material_; }

Transform* const Drone::GetTransform() const noexcept {
  return this->transform_;
}

Vector<float>* const Drone::GetPosition() const noexcept {
  return this->transform_->GetPosition();
}
