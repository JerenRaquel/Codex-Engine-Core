#ifndef ENGINE_HPP_
#define ENGINE_HPP_

class RenderEngine;
class Camera;
class InputSystem;
class Engine;
class Action;
class Scene;
class TextHandler;

// Std
#include <string>
#include <vector>
#include <map>
#include <random>
// Engine
#include "util/helpers.hpp"
#include "util/vector.hpp"
#include "renderEngine.hpp"
#include "camera.hpp"
#include "compute_shaders/computeShaderCompiler.hpp"
#include "compute_shaders/computeShader.hpp"
#include "compute_shaders/computeShaderBuffer.hpp"
#include "mesh.hpp"
#include "action.hpp"
#include "ui/button.hpp"
#include "scene.hpp"
#include "inputSystem.hpp"
// Libs
#include "uuid_v4.h"
#include "mat4x4.hpp"

class Engine {
 private:
  // Engine Data
  std::vector<std::string>* args_;
  Vector<int> windowSize_;
  RenderEngine* renderer_;
  Camera* camera_;
  InputSystem* inputSystem_;
  Action* mainAction_;
  UUIDv4::UUIDGenerator<std::mt19937_64>* uuidGenerator_;

  // Compute shaders
  ComputeShaderCompiler* computeShaderCompiler_;
  std::map<std::string, ComputeShader*>* computeShaders_;
  std::map<std::string, ComputeShaderBuffer*>* computeShaderBuffers_;

  // Scene Data
  std::map<std::string, Scene*>* scenes_;
  Scene* currentScene_;
  std::string currentSceneName_;

  void CreatePrimativeMeshes() const noexcept;
  void Start();

 public:
  Engine(const Vector<int>& windowSize, const std::string& name,
         const std::vector<std::string>& args, Action* mainAction);
  ~Engine();

  // Utility
  void CompileComputeShader(const std::string& computeFile,
                            const std::string& name) const;
  ComputeShaderBuffer* const AssignNewComputeShaderBuffer(
      const std::string& name, const unsigned int& width,
      const unsigned int& height) const;
  Scene* const AddScene(const std::string& name, Scene* scene);
  Scene* const SetCurrentScene(const std::string& name);
  std::string GenerateUUID() const noexcept;

  // Getters
  RenderEngine* const GetRenderer() const noexcept;
  Vector<int> GetWindowSize() const noexcept;
  std::vector<std::string>* const GetArgs() const noexcept;
  ComputeShader* const GetComputeShader(const std::string& name) const;
  ComputeShaderBuffer* const GetComputeShaderBuffer(
      const std::string& name) const noexcept;
  InputSystem* const GetInputSystem() const noexcept;
  Scene* const GetCurrentScene() const noexcept;
};
#endif  // ENGINE_HPP_