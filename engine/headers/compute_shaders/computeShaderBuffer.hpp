#ifndef COMPUTESHADERBUFFER_HPP_
#define COMPUTESHADERBUFFER_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <stdexcept>

class ComputeShaderBuffer {
 private:
  GLuint bufferID_;
  unsigned int width_;
  unsigned int height_;
  unsigned int dataSize_;
  bool bufferCreated_ = false;

 public:
  ComputeShaderBuffer(const unsigned int& width, const unsigned int& height);
  ~ComputeShaderBuffer();

  // Utility
  void CreateBuffer(const unsigned int& dataSize, void* data) noexcept;
  void UpdateBuffer(const unsigned int& dataSize, void* data) const;
  void ReadBuffer(const unsigned int& dataSize, void* data) const;
  void Bind() const;
  void Unbind() const noexcept;

  // Getters
  const unsigned int& GetWidth() const noexcept;
  const unsigned int& GetHeight() const noexcept;
};
#endif  // COMPUTESHADERBUFFER_HPP_