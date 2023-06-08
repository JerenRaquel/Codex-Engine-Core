#ifndef INPUTSYSTEM_HPP_
#define INPUTSYSTEM_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Engine
#include "vector.hpp"
#include "renderEngine.hpp"

class InputSystem {
 private:
  // Mouse Data
  Vector<float> mousePosition_;
  bool isMouseDown_ = false;

 public:
  InputSystem();
  ~InputSystem();

  // Utility
  void Update(GLFWwindow* const window) noexcept;

  // Getters
  Vector<float> GetMousePosition() const noexcept;
  bool IsMouseDown() const noexcept;
};
#endif  // INPUTSYSTEM_HPP_