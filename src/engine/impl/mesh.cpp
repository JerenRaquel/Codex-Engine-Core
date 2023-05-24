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

  this->modelMatrix_ = new glm::mat4x4(1.0f);
  this->CreateBuffer();
}

Mesh::~Mesh() { delete this->modelMatrix_; }

void Mesh::Draw() const noexcept {
  Bind();
  glDrawElements(GL_TRIANGLES, this->indicesSize_, GL_UNSIGNED_INT, 0);
  Unbind();
}

Mesh* Mesh::Rotate(const float& angle) noexcept {
  this->rotation_ += angle;
  this->isModelMatrixDirty = true;
  return this;
}

Mesh* Mesh::SetShaderName(const std::string& shaderName) noexcept {
  this->shaderName_ = shaderName;
  return this;
}

Mesh* Mesh::SetColor(const Vector3<float>& color) noexcept {
  this->color_ = color;
  return this;
}

Mesh* Mesh::SetColor(const float& r, const float& g, const float& b) noexcept {
  this->color_ = Vector3<float>(r, g, b);
  return this;
}

Mesh* Mesh::SetScale(const Vector<float>& scale) noexcept {
  this->scale_ = scale;
  this->isModelMatrixDirty = true;
  return this;
}

Mesh* Mesh::SetPosition(const Vector<float>& position) noexcept {
  this->position_ = position;
  this->isModelMatrixDirty = true;
  return this;
}

Mesh* Mesh::SetRotation(const float& rotation) noexcept {
  this->rotation_ = rotation;
  while (rotation > 360.0f) {
    this->rotation_ -= 360.0f;
  }
  while (rotation < 0.0f) {
    this->rotation_ += 360.0f;
  }
  this->isModelMatrixDirty = true;
  return this;
}

std::string Mesh::GetShaderName() const noexcept { return this->shaderName_; }

glm::mat4x4* Mesh::GetModelMatrix() noexcept {
  if (this->isModelMatrixDirty) {
    delete this->modelMatrix_;
    this->modelMatrix_ = new glm::mat4x4(1.0f);
    *(this->modelMatrix_) =
        glm::translate(*this->modelMatrix_, this->position_.ToGLMVec3f());
    *(this->modelMatrix_) =
        glm::rotate(*this->modelMatrix_, glm::radians(this->rotation_),
                    glm::vec3(0, 0, -1));
    *(this->modelMatrix_) =
        glm::scale(*this->modelMatrix_, this->scale_.ToGLMVec3f());

    this->isModelMatrixDirty = false;
  }
  return this->modelMatrix_;
}

const Vector3<float>& Mesh::GetColor() const noexcept { return this->color_; }
