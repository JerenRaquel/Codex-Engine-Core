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
#include "../../libs/glm/mat4x4.hpp"
#include "../../libs/glm/gtc/matrix_transform.hpp"

class Mesh {
 private:
  // Mesh Data
  GLuint VBO_, EBO_, VAO_;
  GLfloat* vertices_ = nullptr;
  unsigned int verticesSize_ = 0;
  GLuint* indices_ = nullptr;
  unsigned int indicesSize_ = 0;

  // Transform
  glm::mat4x4* modelMatrix_;
  bool isModelMatrixDirty = true;
  Vector<float> position_;
  Vector<float> scale_ = Vector<float>(1.0f, 1.0f);

  // Material
  std::string shaderName_ = "default";
  Vector3<float> color_ = Vector3<float>(1.0f, 1.0f, 1.0f);

  void CreateBuffer();
  void Bind() const noexcept;
  void Unbind() const noexcept;

 public:
  Mesh(GLfloat* vertices, unsigned int verticesSize, GLuint* indices,
       unsigned int indicesSize);
  ~Mesh();

  // Utility
  void Draw() const noexcept;
  // Setters
  Mesh* SetShaderName(const std::string& shaderName) noexcept;
  Mesh* SetColor(const Vector3<float>& color) noexcept;
  Mesh* SetColor(const float& r, const float& g, const float& b) noexcept;
  Mesh* SetScale(const Vector<float>& scale) noexcept;
  Mesh* SetPosition(const Vector<float>& position) noexcept;
  // Getters
  std::string GetShaderName() const noexcept;
  glm::mat4x4* GetModelMatrix() noexcept;
  const Vector3<float>& GetColor() const noexcept;
};
#endif  // MESH_HPP_