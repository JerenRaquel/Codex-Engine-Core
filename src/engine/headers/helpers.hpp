#ifndef HELPERS_HPP_
#define HELPERS_HPP_

// Std
#include <cmath>
// Engine
#include "vector.hpp"

float Lerp(float a, float b, float rate) noexcept;
float Distance(float x, float y) noexcept;
float SqrDistance(float x, float y) noexcept;
float Clamp(float value, float min, float max) noexcept;
Vector3<float> GenerateRandomColor() noexcept;

#endif  // HELPERS_HPP_