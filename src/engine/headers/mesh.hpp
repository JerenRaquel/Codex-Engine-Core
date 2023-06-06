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

  // Transform
  glm::mat4x4* modelMatrix_;
  bool isModelMatrixDirty = true;
  Vector<float>* position_;
  float rotation_ = 0.0f;
  Vector<float> scale_ = Vector<float>(1.0f, 1.0f);

  // Material
  std::string shaderName_ = "default";
  Vector3<float> color_ = Vector3<float>(1.0f, 1.0f, 1.0f);

  void CreateBuffer();
  void Bind() const noexcept;
  void Unbind() const noexcept;

 public:
  Mesh(GLfloat* vertices, unsigned int verticesSize, GLuint* indices,
       unsigned int indicesSize, Vector<float>* position);
  ~Mesh();

  // Utility
  void Draw() const noexcept;
  Mesh* Rotate(const float& angle) noexcept;
  Mesh* RotateTowards(const Vector<float>& direction) noexcept;
  Mesh* RotateTowards(const Vector<float>& direction,
                      const float& bais) noexcept;
  Mesh* Translate(const Vector<float>& direction,
                  const float& magnitude) noexcept;
  // Setters
  Mesh* SetShaderName(const std::string& shaderName) noexcept;
  Mesh* SetColor(const Vector3<float>& color) noexcept;
  Mesh* SetColor(const float& r, const float& g, const float& b) noexcept;
  Mesh* SetScale(const Vector<float>& scale) noexcept;
  Mesh* SetPosition(const Vector<float>& position) noexcept;
  Mesh* SetPosition(const float& x, const float& y) noexcept;
  Mesh* SetRotation(const float& angle) noexcept;
  // Getters
  std::string GetShaderName() const noexcept;
  glm::mat4x4* GetModelMatrix() noexcept;
  const Vector3<float>& GetColor() const noexcept;
  Vector<float> GetDirectionVector() const noexcept;
  const float GetRotation() const noexcept;
};
#endif  // MESH_HPP_