#include "../headers/helpers.hpp"

float Lerp(float a, float b, float rate) noexcept { return a + (b - a) * rate; }

float Distance(float x, float y) noexcept { return sqrt(x * x + y * y); }

float Clamp(float value, float min, float max) noexcept {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}
