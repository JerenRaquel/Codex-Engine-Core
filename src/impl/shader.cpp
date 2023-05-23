#include "../headers/shader.hpp"

Shader::Shader(ShaderCompiler* compiler, const std::string& vertexFile,
               const std::string& fragmentFile) {
  compiler->LoadShaders(vertexFile, fragmentFile);
  compiler->CompileShader(this->shaderID_);
}

Shader::~Shader() { glDeleteProgram(this->shaderID_); }

void Shader::PassUniform3f(const char* name,
                           const Vector3<float>& data) const noexcept {
  GLuint ID = glGetUniformLocation(this->shaderID_, name);
  glUniform3f(ID, data.x, data.y, data.z);
}

void Shader::PassUniformMatrix(const char* name,
                               glm::mat4x4* data) const noexcept {
  GLuint ID = glGetUniformLocation(this->shaderID_, name);
  glUniformMatrix4fv(ID, 1, GL_FALSE, &(*data)[0][0]);
}

void Shader::Use() noexcept { glUseProgram(this->shaderID_); }

GLuint* Shader::GetProgram() noexcept { return &this->shaderID_; }
