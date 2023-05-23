#ifndef QUAD_HPP_
#define QUAD_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <string>
// Custom
#include "vector.hpp"
// Lib
#include "../libs/glm/mat4x4.hpp"
#include "../libs/glm/gtc/matrix_transform.hpp"

class Quad {
 private:
  std::string shaderName_ = "default";
  Vector<float> position_;
  Vector<float> size_;
  Vector<float> scale_ = Vector<float>(1.0f, 1.0f);
  GLuint VBO_, EBO_, VAO_;
  GLfloat* vertices_ = nullptr;
  GLuint* indices_ = nullptr;
  glm::mat4x4* modelMatrix_;
  Vector3<float> color_ = Vector3<float>(1.0f, 1.0f, 1.0f);

  void CreateBuffer();

 public:
  Quad();
  Quad(const Vector<float>& size);
  Quad(const Vector<float>& size, const Vector<float>& position);
  ~Quad();

  // Utility
  void Bind() const noexcept;
  void Unbind() const noexcept;
  void Draw() const noexcept;
  // Setters
  Quad* SetShaderName(const std::string& shaderName) noexcept;
  Quad* SetScale(const Vector<float>& scale) noexcept;
  Quad* SetPosition(const Vector<float>& position) noexcept;
  Quad* SetColor(const Vector3<float>& color) noexcept;
  Quad* SetColor(const float& r, const float& g, const float& b) noexcept;
  // Getters
  std::string GetShaderName() const noexcept;
  glm::mat4x4* GetModelMatrix() noexcept;
  const Vector3<float>& GetColor() const noexcept;
};
#endif  // QUAD_HPP_