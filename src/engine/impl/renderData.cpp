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
void MeshRenderData::PassUniforms(const Shader* const shader,
                                  Camera* const camera) const noexcept {
  glm::mat4x4 mvp =
      *(camera->GetViewOrthoMatrix()) * *(this->transform_->GetModelMatrix());
  shader->PassUniformMatrix("mvp", &mvp);
  shader->PassUniform3f("color", this->material_->GetColor());
  shader->PassUniform1f("alpha", this->material_->GetAlpha());

  bool hasTexture = this->material_->BindTexture();
  shader->PassUniformBool("useTexture", hasTexture);
  shader->PassUniformBool(
      "useBackgroundColor",
      hasTexture ? this->material_->GetBackgroundTextureState() : false);
}

void MeshRenderData::UnbindTexture() const noexcept {
  this->material_->UnbindTexture();
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
                               const Vector<int>& position,
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

const Vector<int>& TextRenderData::GetPosition() const noexcept {
  return this->position_;
}

const float TextRenderData::GetScale() const noexcept { return this->scale_; }
