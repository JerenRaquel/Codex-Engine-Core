#ifndef BOXCOLLIDER_HPP_
#define BOXCOLLIDER_HPP_

// Engine
#include "util/vector2.hpp"
#include "Transform.hpp"

class BoxCollider {
 private:
  //  A----B
  //  |    |
  //  C----D
  Vector2<float> pointA_;
  Vector2<float> pointB_;
  Vector2<float> pointC_;
  Vector2<float> pointD_;
  Transform* transform_ = nullptr;

 public:
  BoxCollider(Transform* const transform);
  ~BoxCollider();

  // Overloads
  Vector2<float> const& operator[](int index) const {
    switch (index) {
      case 0:
        return this->pointA_;
      case 1:
        return this->pointB_;
      case 2:
        return this->pointC_;
      case 3:
        return this->pointD_;
      default:
        throw std::out_of_range("Getting non-existant point in BoxCollider");
    }
  }

  // Utility
  bool IsCollidingInsideOther(const BoxCollider& other) const noexcept;
  void Update() noexcept;

  // Getters
  Vector2<float> GetPointA() const noexcept;
  Vector2<float> GetPointB() const noexcept;
  Vector2<float> GetPointC() const noexcept;
  Vector2<float> GetPointD() const noexcept;
  Vector2<float> GetCenter() const noexcept;
};
#endif  // BOXCOLLIDER_HPP_