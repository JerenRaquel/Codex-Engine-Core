#ifndef COMPUTESHADER_HPP_
#define COMPUTESHADER_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <string>
// Custom
#include "vector.hpp"
#include "computeShaderCompiler.hpp"
#include "computeShaderBuffer.hpp"

class ComputeShader {
 private:
  GLuint shaderID_;
  bool isBinded_ = false;

 public:
  ComputeShader(ComputeShaderCompiler* compiler,
                const std::string& computeFile);
  ~ComputeShader();

  // Utility
  void BindDataBufferAndUse(
      const ComputeShaderBuffer* const shaderBuffer) noexcept;
  void DispatchAndWait(const ComputeShaderBuffer* const shaderBuffer);

  // Pass Uniforms
  void PassUniform1f(const char* name, const float& value) const noexcept;
  void PassUniform2f(const char* name, const float& value1,
                     const float& value2) const noexcept;
  void PassUniform2f(const char* name,
                     const Vector<float>& data) const noexcept;
};
#endif  // COMPUTESHADER_HPP_