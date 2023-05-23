#ifndef SHADERCOMPILER_HPP_
#define SHADERCOMPILER_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

class ShaderCompiler {
 private:
  const std::string shaderPath_ = "../src/shaders/";
  std::string vertexShader_;
  std::string fragmentShader_;

  void ValidateShader(GLuint shaderID, const char* fileName) const noexcept;

 public:
  ShaderCompiler();
  ~ShaderCompiler();

  void LoadShaders(const std::string& vertexFile,
                   const std::string& fragmentFile);
  void CompileShader(GLuint& shaderProgram);
};
#endif  // SHADERCOMPILER_HPP_