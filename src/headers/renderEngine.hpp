#ifndef RENDERENGINE_HPP_
#define RENDERENGINE_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <iostream>
#include <string>
// Custom
#include "errorHandler.hpp"
#include "vector.hpp"

class RenderEngine {
 private:
  GLFWwindow* window_;

 public:
  RenderEngine(const Vector2& size, const std::string& name);
  ~RenderEngine();
  void Start();
};
#endif  // RENDERENGINE_HPP_