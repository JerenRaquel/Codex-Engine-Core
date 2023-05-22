#include "../headers/quad.hpp"

void Quad::CreateBuffer() {
  glGenVertexArrays(1, &this->VAO_);
  glGenBuffers(1, &this->VBO_);
  glGenBuffers(1, &this->EBO_);

  glBindVertexArray(this->VAO_);

  glBindBuffer(GL_ARRAY_BUFFER, this->VBO_);
  GLfloat verts[] = {
      this->position_.x,
      this->position_.y,
      0.0f,  // top left
      this->position_.x + this->size_.x,
      this->position_.y,
      0.0f,  // top right
      this->position_.x + this->size_.x,
      this->position_.y + this->size_.y,
      0.0f,  // bottom right
      this->position_.x,
      this->position_.y + this->size_.y,
      0.0f  // bottom left
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

void Quad::Bind() {
  glBindVertexArray(this->VAO_);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_);
}

void Quad::Unbind() { glBindVertexArray(0); }

void Quad::Draw() {
  Bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  Unbind();
}