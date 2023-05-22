#include "../headers/vector.hpp"

template <typename T>
Vector<T>::Vector() : x(0), y(0) {}

template <typename T>
Vector<T>::Vector(T x, T y) : x(x), y(y) {}

template <typename T>
Vector<T>::~Vector() {}

// Instantiate the template
template class Vector<int>;
template class Vector<float>;