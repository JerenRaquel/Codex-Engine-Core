#include "../headers/quad.hpp"

Quad::Quad() { this = new Quad(Vector2(25f, 25f), Vector2(0, 0)); }

Quad::Quad(const Vector2& size) { this = new Quad(size, Vector2(0, 0)); }

Quad::Quad(const Vector2& size, const Vector2& position) {
  this->size_ = size;
  this->position_ = position;
}

Quad::~Quad() {}