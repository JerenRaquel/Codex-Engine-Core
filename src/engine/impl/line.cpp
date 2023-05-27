#include "../headers/line.hpp"

int Line::Orientation(const Vector<float>& a, const Vector<float>& b,
                      const Vector<float>& c) const noexcept {
  int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
  if (val == 0) {
    return 0;
  } else if (val > 0) {
    return 1;  // clockwise
  } else {
    return 2;  // counterclockwise
  }
}

bool Line::OnSegment(const Vector<float>& a, const Vector<float>& b,
                     const Vector<float>& c) const noexcept {
  float bigX = a.x;
  float bigY = a.y;
  float smallX = b.x;
  float smallY = b.y;
  if (a.x < b.x) {
    bigX = b.x;
    smallX = a.x;
  }
  if (a.y < b.y) {
    bigY = b.y;
    smallY = a.y;
  }

  return c.x <= bigX && c.x >= smallX && c.y <= bigY && c.y >= smallY;
}

Line::Line(const Vector<float>& start, const Vector<float>& end)
    : start_(start), end_(end) {}

Line::~Line() {}

bool Line::IsIntersecting(const Line& other) const noexcept {
  int o1 = Orientation(this->start_, this->end_, other.GetStart());
  int o2 = Orientation(this->start_, this->end_, other.GetEnd());
  int o3 = Orientation(other.GetStart(), other.GetEnd(), this->start_);
  int o4 = Orientation(other.GetStart(), other.GetEnd(), this->end_);

  if (o1 != o2 && o3 != o4) return true;

  if (o1 == 0 && OnSegment(this->start_, other.GetStart(), this->end_))
    return true;
  if (o2 == 0 && OnSegment(this->start_, other.GetEnd(), this->end_))
    return true;
  if (o3 == 0 && OnSegment(other.GetStart(), this->start_, other.GetEnd()))
    return true;
  if (o4 == 0 && OnSegment(other.GetStart(), this->end_, other.GetEnd()))
    return true;

  return false;
}

const Vector<float>& Line::GetStart() const noexcept { return this->start_; }

const Vector<float>& Line::GetEnd() const noexcept { return this->end_; }

Line Line::operator=(const Line& other) noexcept {
  this->start_ = other.start_;
  this->end_ = other.end_;
  return *this;
}

Line Line::operator*(const glm::mat4x4* const modelMatrix) const noexcept {
  glm::vec4 start = glm::vec4(this->start_.x, this->start_.y, 0.0f, 1.0f);
  glm::vec4 end = glm::vec4(this->end_.x, this->end_.y, 0.0f, 1.0f);
  start = *modelMatrix * start;
  end = *modelMatrix * end;

  return Line(Vector<float>(start.x, start.y), Vector<float>(end.x, end.y));
}
