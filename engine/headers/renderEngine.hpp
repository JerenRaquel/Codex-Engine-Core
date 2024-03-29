#ifndef RENDERENGINE_HPP_
#define RENDERENGINE_HPP_

// PreInclude
#include "ui/imgui/guiManager.hpp"  // Includes GLFW
// Std
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <map>
#include <queue>
// Lib
#include "mat4x4.hpp"
// Custom
#include "util/vector3.hpp"
#include "mesh.hpp"
#include "shaders/shader.hpp"
#include "shaders/shaderCompiler.hpp"
#include "camera.hpp"
#include "ui/textHandler.hpp"
#include "material.hpp"
#include "transform.hpp"
#include "renderData.hpp"
#include "scene.hpp"

class RenderEngine {
 private:
  //* OpenGL
  GLFWwindow* window_;

  //* GUI
  GuiManager* guiManager_;

  //* Mesh Data
  // Freed Here as well as content
  std::map<std::string, Mesh*>* meshTypes_ = nullptr;

  //* Texture Data
  std::map<std::string, TextureData*>* textures_;

  //* Shader Data
  ShaderCompiler* shaderCompiler_;
  std::map<std::string, Shader*>* shaders_;
  std::vector<std::string>* shaderNames_;

  //* Text Data
  TextHandler* textHandler_;
  std::string defaultTextShaderName_;

  //* Methods
  void InitOpenGL(const Vector2<int>& size, const std::string& name);
  void RenderMeshBatch(
      const glm::mat4x4& cameraMatrix,
      std::vector<MeshRenderData*>* const meshRenderData) const noexcept;
  void RenderTextBatch(
      std::vector<TextRenderData*>* const textRenderData) const noexcept;

 public:
  RenderEngine(const Vector2<int>& size, const std::string& name,
               const std::string& defaultFontFile,
               const std::string& textShaderName);
  ~RenderEngine();
  void Render(Camera* const camera, const Scene* const scene) const noexcept;
  void CompileShader(const std::string& vertex, const std::string& fragment,
                     const std::string& name);
  void AddMeshType(const std::string& name, Mesh* const mesh);
  void AddTexture(const std::string& name, const std::string& path);
  void AddTexture(const std::string& name, const std::string& path,
                  int cellWidth, int cellHeight);

  // Getters
  Shader* const GetShader(const std::string& name);
  TextureData* const GetTextureData(const std::string& name) const;
  GLFWwindow* const GetWindow() const noexcept;
  GuiManager* const GetGuiManager() const noexcept;
  const Vector2<float> GetTextSize(const std::string& text,
                                   const float& scale) const noexcept;
};
#endif  // RENDERENGINE_HPP_