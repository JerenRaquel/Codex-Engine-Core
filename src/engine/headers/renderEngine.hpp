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
// Custom
#include "vector.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "shaderCompiler.hpp"
#include "camera.hpp"
#include "textHandler.hpp"

class RenderEngine {
 private:
  // structs
  struct TextMetaData {
    std::string text;
    Vector<int> position;
    Vector3<float> color;
    int scale;
  };

  // OpenGL
  GLFWwindow* window_;

  // Mesh Data
  std::vector<Mesh*>* meshPointer_ = nullptr;

  // Shader Data
  ShaderCompiler* shaderCompiler_;
  std::map<std::string, Shader*>* shaders_;
  std::vector<std::string>* shaderNames_;

  // Text Data
  TextHandler* textHandler_;
  std::string defaultTextShaderName_;
  std::queue<TextMetaData>* textMetaData_;

  // Methods
  void InitOpenGL(const Vector<int>& size, const std::string& name);
  void RenderMeshBatch(const glm::mat4x4* const orthoViewMatrix) const noexcept;
  void RenderTextBatch(const glm::mat4x4* const orthoMatrix) const noexcept;

 public:
  RenderEngine(const Vector<int>& size, const std::string& name,
               const std::string& defaultFontFile,
               const std::string& textShaderName);
  ~RenderEngine();
  void Render(const glm::mat4x4* const orthoViewMatrix);
  void DrawText(const std::string& text, const Vector<int>& position,
                const int& scale) const noexcept;
  void DrawText(const std::string& text, const Vector<int>& position,
                const Vector3<float>& color, const int& scale) const noexcept;
  void CompileShader(const std::string& vertex, const std::string& fragment,
                     const std::string& name);

  void SetMeshPointer(std::vector<Mesh*>* meshPointer) noexcept;
  Shader* const GetShader(const std::string& name);
  GLFWwindow* const GetWindow() const noexcept;
};
#endif  // RENDERENGINE_HPP_