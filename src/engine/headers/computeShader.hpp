#ifndef COMPUTESHADER_HPP_
#define COMPUTESHADER_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <string>
// Custom
#include "computeShaderCompiler.hpp"

class ComputeShader {
 private:
  GLuint shaderID_;

 public:
  ComputeShader(ComputeShaderCompiler* compiler,
                const std::string& computeFile);
  ~ComputeShader();

  void Use(const unsigned int& width, const unsigned int& height) noexcept;
};
#endif  // COMPUTESHADER_HPP_