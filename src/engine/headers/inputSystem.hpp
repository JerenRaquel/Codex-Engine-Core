#ifndef INPUTSYSTEM_HPP_
#define INPUTSYSTEM_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <vector>
#include <map>
// Engine
#include "util/vector.hpp"
#include "renderEngine.hpp"

class InputSystem {
 public:
  struct DirectionCallback {
    void* object;
    void (*func)(void* object, const Vector<float>& direction);
  };
  struct KeyCallback {
    void* object;
    void (*func)(void* object);
  };

 private:
  Vector<int> windowSize_;
  std::vector<DirectionCallback> directionUpdateEvents_;
  std::map<int, std::vector<KeyCallback>> keyPressEvents_;

  // Mouse Data
  Vector<float> mousePosition_;
  bool isMouseDown_ = false;

 public:
  InputSystem(const Vector<int>& windowSize);
  ~InputSystem();

  // Utility
  void Update(GLFWwindow* const window) noexcept;

  // Events
  void AssignOnDirectionUpdate(DirectionCallback callback) noexcept;
  void AssignOnKeyPress(int key, KeyCallback callback) noexcept;

  // Getters
  Vector<float> GetMousePosition() const noexcept;
  bool IsMouseDown() const noexcept;
};
#endif  // INPUTSYSTEM_HPP_