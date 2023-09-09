#include "compute_shaders/computeShaderBuffer.hpp"

ComputeShaderBuffer::ComputeShaderBuffer(const unsigned int& width,
                                         const unsigned int& height)
    : width_(width), height_(height) {}

ComputeShaderBuffer::~ComputeShaderBuffer() {
  glDeleteBuffers(1, &this->bufferID_);
}

void ComputeShaderBuffer::CreateBuffer(const unsigned int& dataSize,
                                       void* data) noexcept {
  this->dataSize_ = dataSize;

  glGenBuffers(1, &this->bufferID_);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->bufferID_);
  glBufferData(GL_SHADER_STORAGE_BUFFER, dataSize, data, GL_DYNAMIC_COPY);
  this->Unbind();
  this->bufferCreated_ = true;
}

void ComputeShaderBuffer::UpdateBuffer(const unsigned int& dataSize,
                                       void* data) const {
  if (!this->bufferCreated_) {
    throw std::runtime_error("Buffer not created yet!");
  }
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->bufferID_);
  GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
  memcpy(p, data, dataSize);
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
  this->Unbind();
}

void ComputeShaderBuffer::ReadBuffer(const unsigned int& dataSize,
                                     void* data) const {
  if (!this->bufferCreated_) {
    throw std::runtime_error("Buffer not created yet!");
  }
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->bufferID_);
  GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
  memcpy(data, p, dataSize);
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
  this->Unbind();
}

void ComputeShaderBuffer::Bind() const {
  if (!this->bufferCreated_) {
    throw std::runtime_error("Buffer not created yet!");
  }
  glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 0, this->bufferID_, 0,
                    this->dataSize_);
}

void ComputeShaderBuffer::Unbind() const noexcept {
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

// Getters
const unsigned int& ComputeShaderBuffer::GetWidth() const noexcept {
  return this->width_;
}

const unsigned int& ComputeShaderBuffer::GetHeight() const noexcept {
  return this->height_;
}
