#ifndef SHADER_HPP_
#define SHADER_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <map>
#include <vector>
// Custom
#include "shaderCompiler.hpp"
#include "util/vector3.hpp"
// Lib
#include "mat4x4.hpp"
#include "gtc/type_ptr.hpp"

class Shader {
 private:
  GLuint shaderID_;

 public:
  Shader(ShaderCompiler* compiler, const std::string& vertexFile,
         const std::string& fragmentFile);
  ~Shader();

  // Utility
  void PassUniformBool(const char* name, const bool& state) const noexcept;
  void PassUniform1i(const char* name, const int& data) const noexcept;
  void PassUniform3i(const char* name, const Vector3<int>& data) const noexcept;
  void PassUniform1f(const char* name, const float& data) const noexcept;
  void PassUniform3f(const char* name,
                     const Vector3<float>& data) const noexcept;
  void PassUniformMatrix(const char* name, glm::mat4x4* data) const noexcept;
  void PassUniformMatrix(const char* name,
                         const glm::mat4x4* data) const noexcept;

  void Use() noexcept;

  GLuint* GetProgram() noexcept;
};
#endif  // SHADER_HPP_