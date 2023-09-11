#include "renderData.hpp"

//
// MeshRenderData
//
MeshRenderData::MeshRenderData(const std::string& meshType, Material* material,
                               Transform* transform) {
  this->meshType_ = meshType;
  this->material_ = material;
  this->transform_ = transform;
}

MeshRenderData::~MeshRenderData() {}

// Utility
void MeshRenderData::PassUniforms(
    const Shader* const shader,
    const glm::mat4x4& cameraMatrix) const noexcept {
  glm::mat4x4 mvp = cameraMatrix * *(this->transform_->GetModelMatrix());
  shader->PassUniformMatrix("mvp", &mvp);
  shader->PassUniform3f("color", this->material_->GetColor());
  shader->PassUniform1f("alpha", this->material_->GetAlpha());

  // Texture
  this->material_->BindTextureData(shader);
}

void MeshRenderData::UnbindTexture() const noexcept {
  this->material_->UnbindTextureData();
}

// Getters
const std::string& MeshRenderData::GetMeshType() const noexcept {
  return this->meshType_;
}

Material* const MeshRenderData::GetMaterial() const noexcept {
  return this->material_;
}

Transform* const MeshRenderData::GetTransform() const noexcept {
  return this->transform_;
}

//
// TextRenderData
//
TextRenderData::TextRenderData(const std::string& text,
                               const Vector2<int>& position)
    : TextRenderData(text, position, Vector3<float>(1.0f, 1.0f, 1.0f), 1.0f) {}

TextRenderData::TextRenderData(const std::string& text,
                               const Vector2<int>& position,
                               const Vector3<float>& color)
    : TextRenderData(text, position, color, 1.0f) {}

TextRenderData::TextRenderData(const std::string& text,
                               const Vector2<int>& position,
                               const Vector3<float>& color,
                               const float& scale) {
  this->text_ = text;
  this->position_ = position;
  this->color_ = color;
  this->scale_ = scale;
}

TextRenderData::~TextRenderData() {}

// Getters
const std::string& TextRenderData::GetText() const noexcept {
  return this->text_;
}

const Vector2<int>& TextRenderData::GetPosition() const noexcept {
  return this->position_;
}

const float TextRenderData::GetScale() const noexcept { return this->scale_; }
