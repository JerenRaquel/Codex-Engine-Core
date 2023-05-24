#include "../headers/vector.hpp"

template <typename T>
Vector<T>::Vector() : x(0), y(0) {}

template <typename T>
Vector<T>::Vector(T x, T y) : x(x), y(y) {}

template <typename T>
Vector<T>::~Vector() {}

template <typename T>
Vector3<T>::Vector3() : x(0), y(0), z(0) {}

template <typename T>
Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

template <typename T>
Vector3<T>::~Vector3() {}

// Instantiate the template
template class Vector<int>;
template class Vector<float>;
template class Vector3<int>;
template class Vector3<float>;