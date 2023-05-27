#include "../headers/outlineCollider.hpp"

OutlineCollider::OutlineCollider(
    const float* const vertices, const unsigned int& verticesSize,
    const std::vector<unsigned int>& verticesOrder) {
  if (verticesSize % 3 != 0) {
    throw std::invalid_argument(  // TEMP
        "Vertices size must be a multiple of 3 [x, y, z]\nTo be changed "
        "later...");
  }

  this->lines_ = new std::vector<Line*>();
  unsigned int pointCount = verticesSize / 3;
  Vector<float> points[pointCount];
  for (unsigned int i = 0; i < pointCount; i++) {
    // TEMP: z is ignored
    points[i] = Vector<float>(vertices[i * 3], vertices[i * 3 + 1]);
  }

  for (unsigned int i = 0; i < verticesOrder.size() - 1; i++) {
    this->lines_->push_back(
        new Line(points[verticesOrder[i]], points[verticesOrder[i + 1]]));
  }
  this->lines_->push_back(
      new Line(points[verticesOrder[verticesOrder.size() - 1]],
               points[verticesOrder[0]]));
}

OutlineCollider::~OutlineCollider() {
  for (auto& line : *this->lines_) {
    delete line;
  }
  delete this->lines_;
}

bool OutlineCollider::IsColliding(const glm::mat4x4* const modelMatrix,
                                  const Line& other) const noexcept {
  for (Line* line : *this->lines_) {
    Line transformedLine = *line * modelMatrix;
    if (transformedLine.IsIntersecting(other)) {
      return true;
    }
  }
  return false;
}