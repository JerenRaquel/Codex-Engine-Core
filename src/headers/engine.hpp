#ifndef ENGINE_HPP_
#define ENGINE_HPP_

// Std
#include <string>
// Custom
#include "vector.hpp"
#include "renderEngine.hpp"
#include "camera.hpp"

class Engine {
 private:
  Vector<int> windowSize_;
  RenderEngine* renderer_;
  Camera* camera_;
  void MoveCamera() noexcept;
  void OnStart() noexcept;
  void OnUpdate() noexcept;

 public:
  Engine(const Vector<int>& windowSize, const std::string& name);
  ~Engine();

  void Start();
};
#endif  // ENGINE_HPP_