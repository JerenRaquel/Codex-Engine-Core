#ifndef RENDERENGINE_HPP_
#define RENDERENGINE_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
// Custom
#include "vector.hpp"
#include "quad.hpp"

class RenderEngine {
 private:
  GLFWwindow* window_;
  std::vector<Quad*>* quads_;

 public:
  RenderEngine(const Vector<int>& size, const std::string& name);
  ~RenderEngine();
  void Start();
  void AddQuad(Quad* quad);
};
#endif  // RENDERENGINE_HPP_