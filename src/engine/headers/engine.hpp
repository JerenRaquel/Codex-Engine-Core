#ifndef ENGINE_HPP_
#define ENGINE_HPP_

class RenderEngine;
class Camera;
class Engine;
class Action;

// Std
#include <string>
#include <vector>
#include <map>
// Custom
#include "helpers.hpp"
#include "vector.hpp"
#include "renderEngine.hpp"
#include "camera.hpp"
#include "compute_shaders/computeShaderCompiler.hpp"
#include "compute_shaders/computeShader.hpp"
#include "compute_shaders/computeShaderBuffer.hpp"
#include "mesh.hpp"
#include "action.hpp"
#include "ui/button.hpp"
// Libs
#include "mat4x4.hpp"

class Engine {
 private:
  // Engine Data
  std::vector<std::string>* args_;
  Vector<int> windowSize_;
  RenderEngine* renderer_;
  Camera* camera_;
  std::vector<Action*>* actions_;

  // Mouse Data
  Vector<float> mousePosition_;
  bool isMouseDown_ = false;

  // Compute shaders
  ComputeShaderCompiler* computeShaderCompiler_;
  std::map<std::string, ComputeShader*>* computeShaders_;
  std::map<std::string, ComputeShaderBuffer*>* computeShaderBuffers_;

  // TEMP - start
  std::vector<RenderData*>* renderData_;
  std::vector<Button*>* buttons_;
  // TEMP - end

  void MoveCamera() noexcept;
  void CalculateMousePosition() noexcept;
  void CreatePrimativeMeshes() const noexcept;

 public:
  Engine(const Vector<int>& windowSize, const std::string& name,
         const std::vector<std::string>& args);
  ~Engine();

  // Utility
  void Start();
  void CompileComputeShader(const std::string& computeFile,
                            const std::string& name) const;
  ComputeShaderBuffer* const AssignNewComputeShaderBuffer(
      const std::string& name, const unsigned int& width,
      const unsigned int& height) const;
  const Engine* const AddAction(Action* action) const noexcept;
  const Engine* const AddButton(Button* button) const noexcept;

  // Getters
  RenderEngine* const GetRenderer() const noexcept;
  Vector<int> GetWindowSize() const noexcept;
  std::vector<std::string>* const GetArgs() const noexcept;
  Vector<float> GetMousePosition() const noexcept;
  ComputeShader* const GetComputeShader(const std::string& name) const;
  ComputeShaderBuffer* const GetComputeShaderBuffer(
      const std::string& name) const noexcept;
};
#endif  // ENGINE_HPP_