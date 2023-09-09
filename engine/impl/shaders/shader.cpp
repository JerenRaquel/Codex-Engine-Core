#include "shaders/shader.hpp"

Shader::Shader(ShaderCompiler* compiler, const std::string& vertexFile,
               const std::string& fragmentFile) {
  compiler->LoadShaders(vertexFile, fragmentFile);
  compiler->CompileShader(this->shaderID_);
}

Shader::~Shader() { glDeleteProgram(this->shaderID_); }

// Utility
void Shader::PassUniformBool(const char* name,
                             const bool& state) const noexcept {
  int ID = glGetUniformLocation(this->shaderID_, name);
  if (ID == -1) return;
  glUniform1i(ID, state ? 1 : 0);
}

void Shader::PassUniform1i(const char* name, const int& data) const noexcept {
  int ID = glGetUniformLocation(this->shaderID_, name);
  if (ID == -1) return;
  glUniform1i(ID, data);
}

void Shader::PassUniform1f(const char* name, const float& data) const noexcept {
  int ID = glGetUniformLocation(this->shaderID_, name);
  if (ID == -1) return;
  glUniform1f(ID, data);
}

void Shader::PassUniform3f(const char* name,
                           const Vector3<float>& data) const noexcept {
  int ID = glGetUniformLocation(this->shaderID_, name);
  if (ID == -1) return;
  glUniform3f(ID, data.x, data.y, data.z);
}

void Shader::PassUniformMatrix(const char* name,
                               glm::mat4x4* data) const noexcept {
  int ID = glGetUniformLocation(this->shaderID_, name);
  if (ID == -1) return;
  glUniformMatrix4fv(ID, 1, GL_FALSE, &(*data)[0][0]);
}

void Shader::PassUniformMatrix(const char* name,
                               const glm::mat4x4* data) const noexcept {
  int ID = glGetUniformLocation(this->shaderID_, name);
  if (ID == -1) return;
  glUniformMatrix4fv(ID, 1, GL_FALSE, &(*data)[0][0]);
}

void Shader::Use() noexcept { glUseProgram(this->shaderID_); }

GLuint* Shader::GetProgram() noexcept { return &this->shaderID_; }
