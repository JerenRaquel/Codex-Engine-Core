#include "util/helpers.hpp"

float Lerp(float a, float b, float rate) noexcept { return a + (b - a) * rate; }

float Distance(float x, float y) noexcept { return sqrt(SqrDistance(x, y)); }

float SqrDistance(float x, float y) noexcept { return x * x + y * y; }

float Clamp(float value, float min, float max) noexcept {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

Vector3<float> GenerateRandomColor() noexcept {
  float r = static_cast<float>(std::rand() % 255) / 255.0f;
  float g = static_cast<float>(std::rand() % 255) / 255.0f;
  float b = static_cast<float>(std::rand() % 255) / 255.0f;
  return Vector3<float>(r, g, b);
}

bool stringEndsWith(const std::string& str,
                    const std::string& suffix) noexcept {
  return str.size() >= suffix.size() &&
         str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
