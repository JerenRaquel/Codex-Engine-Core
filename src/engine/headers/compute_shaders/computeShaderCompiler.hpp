#ifndef COMPUTESHADERCOMPILER_HPP_
#define COMPUTESHADERCOMPILER_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class ComputeShaderCompiler {
 private:
  const std::string shaderPath_ = "../src/shaders/compute/";
  std::string computeShader_;

  void ValidateShader(GLuint shaderID) const noexcept;

 public:
  ComputeShaderCompiler();
  ~ComputeShaderCompiler();

  void LoadShader(const std::string& computeFile);
  void CompileShader(GLuint& shaderProgram);
};
#endif  // COMPUTESHADERCOMPILER_HPP_