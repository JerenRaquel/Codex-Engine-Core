#include "../headers/quad.hpp"

void Quad::CreateBuffer() {
  this->modelMatrix_ = new glm::mat4x4(1.0f);

  glGenVertexArrays(1, &this->VAO_);
  glGenBuffers(1, &this->VBO_);
  glGenBuffers(1, &this->EBO_);

  glBindVertexArray(this->VAO_);

  glBindBuffer(GL_ARRAY_BUFFER, this->VBO_);
  const Vector<float> offset = this->size_ / 2.0f;
  GLfloat verts[] = {
      -offset.x, -offset.y, 0.0f,  // top left
      offset.x,  -offset.y, 0.0f,  // top right
      offset.x,  offset.y,  0.0f,  // bottom right
      -offset.x, offset.y,  0.0f   // bottom left
  };
  this->vertices_ = verts;
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, this->vertices_,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_);
  GLuint indices[] = {
      0, 1, 2,  // first triangle
      2, 3, 0   // second triangle
  };
  this->indices_ = indices;
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, this->indices_,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(0);
}

Quad::Quad() {
  this->size_ = Vector<float>(25, 25);
  this->position_ = Vector<float>(0, 0);
  this->CreateBuffer();
}

Quad::Quad(const Vector<float> &size) {
  this->size_ = size;
  this->position_ = Vector<float>(0, 0);
  this->CreateBuffer();
}

Quad::Quad(const Vector<float> &size, const Vector<float> &position) {
  this->size_ = size;
  this->position_ = position;
  this->CreateBuffer();
}

Quad::~Quad() {
  delete[] this->vertices_;
  delete[] this->indices_;
  glDeleteVertexArrays(1, &this->VAO_);
  glDeleteBuffers(1, &this->VBO_);
  glDeleteBuffers(1, &this->EBO_);
  this->vertices_ = nullptr;
  this->indices_ = nullptr;
}

void Quad::Bind() const noexcept {
  glBindVertexArray(this->VAO_);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_);
}

void Quad::Unbind() const noexcept { glBindVertexArray(0); }

void Quad::Draw() const noexcept {
  Bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  Unbind();
}

Quad *Quad::SetShaderName(const std::string &shaderName) noexcept {
  this->shaderName_ = shaderName;
  return this;
}

Quad *Quad::SetScale(const Vector<float> &scale) noexcept {
  this->scale_ = scale;
  return this;
}

Quad *Quad::SetPosition(const Vector<float> &position) noexcept {
  this->position_ = position;
  return this;
}

Quad *Quad::SetColor(const Vector3<float> &color) noexcept {
  this->color_ = color;
  return this;
}

Quad *Quad::SetColor(const float &r, const float &g, const float &b) noexcept {
  this->color_ = Vector3<float>(r, g, b);
  return this;
}

std::string Quad::GetShaderName() const noexcept { return this->shaderName_; }

glm::mat4x4 *Quad::GetModelMatrix() noexcept {
  delete this->modelMatrix_;
  this->modelMatrix_ = new glm::mat4x4(1.0f);
  *(this->modelMatrix_) =
      glm::translate(*this->modelMatrix_, this->position_.ToGLMVec3f());
  *(this->modelMatrix_) =
      glm::scale(*this->modelMatrix_, this->scale_.ToGLMVec3f());

  return this->modelMatrix_;
}

const Vector3<float> &Quad::GetColor() const noexcept { return this->color_; }