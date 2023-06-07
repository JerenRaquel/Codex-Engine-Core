#ifndef MESH_HPP_
#define MESH_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <string>
// Custom
#include "vector.hpp"
// Lib
#include "mat4x4.hpp"
#include "gtc/matrix_transform.hpp"

class Mesh {
 private:
  // Mesh Data
  GLuint VBO_, EBO_, VAO_;
  GLfloat* vertices_ = nullptr;
  unsigned int verticesSize_ = 0;
  GLuint* indices_ = nullptr;
  unsigned int indicesSize_ = 0;

  void CreateBuffer();
  void Bind() const noexcept;
  void Unbind() const noexcept;

 public:
  Mesh(GLfloat* vertices, unsigned int verticesSize, GLuint* indices,
       unsigned int indicesSize);
  ~Mesh();

  // Utility
  void Draw() const noexcept;
};
#endif  // MESH_HPP_