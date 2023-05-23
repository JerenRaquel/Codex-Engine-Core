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
// Custom
#include "vector.hpp"
#include "quad.hpp"
#include "shader.hpp"
#include "shaderCompiler.hpp"
#include "camera.hpp"

class RenderEngine {
 private:
  GLFWwindow* window_;
  Camera* camera_;
  std::vector<Quad*>* quads_;
  ShaderCompiler* shaderCompiler_;
  std::map<std::string, Shader*>* shaders_;
  std::vector<std::string>* shaderNames_;

 public:
  RenderEngine(const Vector<int>& size, const std::string& name);
  ~RenderEngine();
  void Start();
  Quad* AddQuad(Quad* quad);
  void CompileShader(const std::string& vertex, const std::string& fragment,
                     const std::string& name);
  Shader* const GetShader(const std::string& name);
  Camera* const GetCamera() noexcept;
};
#endif  // RENDERENGINE_HPP_