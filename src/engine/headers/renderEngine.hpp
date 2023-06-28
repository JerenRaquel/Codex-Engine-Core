#ifndef RENDERENGINE_HPP_
#define RENDERENGINE_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
#include "util/vector.hpp"
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

  //* Mesh Data
  // Freed Here as well as content
  std::map<std::string, Mesh*>* meshTypes_ = nullptr;

  //* Shader Data
  ShaderCompiler* shaderCompiler_;
  std::map<std::string, Shader*>* shaders_;
  std::vector<std::string>* shaderNames_;

  //* Text Data
  TextHandler* textHandler_;
  std::string defaultTextShaderName_;

  //* Methods
  void InitOpenGL(const Vector<int>& size, const std::string& name);
  void RenderMeshBatch(
      Camera* const camera,
      std::vector<MeshRenderData*>* const meshRenderData) const noexcept;
  void RenderMeshUIBatch(
      Camera* const camera,
      std::vector<MeshRenderData*>* const meshRenderData) const noexcept;
  void RenderTextBatch(
      std::vector<TextRenderData*>* const textRenderData) const noexcept;

 public:
  RenderEngine(const Vector<int>& size, const std::string& name,
               const std::string& defaultFontFile,
               const std::string& textShaderName);
  ~RenderEngine();
  void Render(Camera* const camera, const Scene* const scene) const noexcept;
  void CompileShader(const std::string& vertex, const std::string& fragment,
                     const std::string& name);
  void AddMeshType(const std::string& name, Mesh* const mesh);

  // Getters
  Shader* const GetShader(const std::string& name);
  GLFWwindow* const GetWindow() const noexcept;
  const Vector<float> GetTextSize(const std::string& text,
                                  const float& scale) const noexcept;
};
#endif  // RENDERENGINE_HPP_