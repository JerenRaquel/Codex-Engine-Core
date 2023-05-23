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

class Shader {
 private:
  struct Data {
    float* data;
    unsigned int amount;
  };

  GLuint shaderID_;
  std::map<const char*, Data*>* uniformData_;
  std::vector<const char*>* shaderIDs_;

 public:
  Shader(ShaderCompiler* compiler, const std::string& vertexFile,
         const std::string& fragmentFile);
  ~Shader();

  void PassUniformData() noexcept;
  void AddUniformDataID(const char* variableName, float* data,
                        unsigned int amount);
  void UpdateUniformData1f(const char* variableName, float data);
  void UpdateUniformData2f(const char* variableName, float* data);
  void UpdateUniformData3f(const char* variableName, float* data);

  void Use() noexcept;

  GLuint* GetProgram() noexcept;
};
#endif  // SHADER_HPP_