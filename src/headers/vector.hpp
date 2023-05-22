#ifndef VECTOR_HPP_
#define VECTOR_HPP_

template <typename T>
class Vector {
 public:
  T x, y;

  Vector<T>();
  Vector<T>(T x, T y);
  ~Vector<T>();

  Vector<T> operator=(const Vector<T>& other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
  }
};

#endif  // VECTOR_HPP_