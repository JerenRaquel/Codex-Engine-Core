#ifndef QUAD_HPP_
#define QUAD_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Custom
#include "vector.hpp"

class Quad {
 private:
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

  void Bind();
  void Unbind();
  void Draw();
};
#endif  // QUAD_HPP_