#ifndef QUAD_HPP_
#define QUAD_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <string>
// Custom
#include "vector.hpp"

class Quad {
 private:
  std::string shaderName_ = "default";
  Vector<float> position_;
  Vector<float> size_;
  GLuint VBO_, EBO_, VAO_;
  GLfloat* vertices_ = nullptr;
  GLuint* indices_ = nullptr;

  void CreateBuffer();

 public:
  Quad();
  Quad(const Vector<float>& size);
  Quad(const Vector<float>& size, const Vector<float>& position);
  ~Quad();

  void SetShaderName(const std::string& shaderName) noexcept;
  void Bind() const noexcept;
  void Unbind() const noexcept;
  void Draw() const noexcept;
  std::string GetShaderName() const noexcept;
};
#endif  // QUAD_HPP_