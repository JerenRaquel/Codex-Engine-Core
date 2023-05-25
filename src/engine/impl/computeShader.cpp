#include "../headers/computeShader.hpp"

ComputeShader::ComputeShader(ComputeShaderCompiler* compiler,
                             const std::string& computeFile) {
  compiler->LoadShader(computeFile);
  compiler->CompileShader(this->shaderID_);
}

ComputeShader::~ComputeShader() { glDeleteProgram(this->shaderID_); }

void ComputeShader::Use(const unsigned int& width,
                        const unsigned int& height) noexcept {
  glUseProgram(this->shaderID_);
  glDispatchCompute(width, height, 1);
  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}
