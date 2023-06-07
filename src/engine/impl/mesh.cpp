#include "../headers/mesh.hpp"

void Mesh::CreateBuffer() {
  glGenVertexArrays(1, &this->VAO_);
  glGenBuffers(1, &this->VBO_);
  glGenBuffers(1, &this->EBO_);

  glBindVertexArray(this->VAO_);

  glBindBuffer(GL_ARRAY_BUFFER, this->VBO_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->verticesSize_,
               this->vertices_, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->indicesSize_,
               this->indices_, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid*)0);
  glEnableVertexAttribArray(0);
}

void Mesh::Bind() const noexcept {
  glBindVertexArray(this->VAO_);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_);
}

void Mesh::Unbind() const noexcept { glBindVertexArray(0); }

Mesh::Mesh(GLfloat* vertices, unsigned int verticesSize, GLuint* indices,
           unsigned int indicesSize) {
  this->vertices_ = new GLfloat[verticesSize];
  for (unsigned int i = 0; i < verticesSize; i++) {
    this->vertices_[i] = vertices[i];
  }
  this->verticesSize_ = verticesSize;

  this->indices_ = new GLuint[indicesSize];
  for (unsigned int i = 0; i < indicesSize; i++) {
    this->indices_[i] = indices[i];
  }
  this->indicesSize_ = indicesSize;

  this->CreateBuffer();
}

Mesh::~Mesh() {
  glDeleteBuffers(1, &this->VBO_);
  glDeleteBuffers(1, &this->EBO_);
  glDeleteBuffers(1, &this->VAO_);
}

void Mesh::Draw() const noexcept {
  Bind();
  glDrawElements(GL_TRIANGLES, this->indicesSize_, GL_UNSIGNED_INT, 0);
  Unbind();
}
