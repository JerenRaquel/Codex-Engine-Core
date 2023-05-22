#ifndef ENGINE_HPP_
#define ENGINE_HPP_

// Std
#include <string>
// Custom
#include "vector.hpp"
#include "renderEngine.hpp"

class Engine {
 private:
  RenderEngine* renderer_;

 public:
  Engine(const Vector2& windowSize, const std::string& name);
  ~Engine();

  void Start();
};
#endif  // ENGINE_HPP_