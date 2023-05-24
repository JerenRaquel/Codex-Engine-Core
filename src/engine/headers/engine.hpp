#ifndef ENGINE_HPP_
#define ENGINE_HPP_

// Std
#include <string>
#include <vector>
// Custom
#include "vector.hpp"
#include "renderEngine.hpp"
#include "camera.hpp"

class Engine {
 private:
  Vector<int> windowSize_;
  RenderEngine* renderer_;
  Camera* camera_;
  std::vector<void (*)(Engine* const engine)>* startFunctions_;
  std::vector<void (*)(Engine* const engine)>* updateFunctions_;

  void MoveCamera() noexcept;
  void OnStart() noexcept;
  void OnUpdate() noexcept;

 public:
  Engine(const Vector<int>& windowSize, const std::string& name);
  ~Engine();

  void Start();
  void AddStartFunction(void (*func)(Engine* const engine)) noexcept;
  void AddUpdateFunction(void (*func)(Engine* const engine)) noexcept;

  // Getters
  RenderEngine* const GetRenderer() const noexcept;
  Vector<int> GetWindowSize() const noexcept;
};
#endif  // ENGINE_HPP_