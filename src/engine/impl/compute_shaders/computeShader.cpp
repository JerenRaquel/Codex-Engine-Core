#include "compute_shaders/computeShader.hpp"

ComputeShader::ComputeShader(ComputeShaderCompiler* compiler,
                             const std::string& computeFile) {
  compiler->LoadShader(computeFile);
  compiler->CompileShader(this->shaderID_);
}

ComputeShader::~ComputeShader() { glDeleteProgram(this->shaderID_); }

void ComputeShader::BindDataBufferAndUse(
    const ComputeShaderBuffer* const shaderBuffer) noexcept {
  glUseProgram(this->shaderID_);
  shaderBuffer->Bind();
  this->isBinded_ = true;
}

void ComputeShader::DispatchAndWait(
    const ComputeShaderBuffer* const shaderBuffer) {
  if (!this->isBinded_) {
    throw std::runtime_error(
        "ERROR: Unable to dispatch compute shader without binding data "
        "address...");
  }

  this->isBinded_ = false;
  glDispatchCompute(shaderBuffer->GetWidth(), shaderBuffer->GetHeight(), 1);
  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  shaderBuffer->Unbind();
}

// Pass Uniforms
void ComputeShader::PassUniform1f(const char* name,
                                  const float& value) const noexcept {
  GLuint ID = glGetUniformLocation(this->shaderID_, name);
  glUniform1f(ID, value);
}

void ComputeShader::PassUniform2f(const char* name, const float& value1,
                                  const float& value2) const noexcept {
  GLuint ID = glGetUniformLocation(this->shaderID_, name);
  glUniform2f(ID, value1, value2);
}

void ComputeShader::PassUniform2f(const char* name,
                                  const Vector<float>& data) const noexcept {
  GLuint ID = glGetUniformLocation(this->shaderID_, name);
  glUniform2f(ID, data.x, data.y);
}
