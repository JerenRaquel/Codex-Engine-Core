#ifndef ENGINE_HPP_
#define ENGINE_HPP_

class Drone;
class DroneManager;
class RenderEngine;
class Camera;
class Engine;

// Std
#include <string>
#include <vector>
#include <map>
// Custom
#include "helpers.hpp"
#include "vector.hpp"
#include "renderEngine.hpp"
#include "camera.hpp"
#include "computeShaderCompiler.hpp"
#include "computeShader.hpp"
#include "computeShaderBuffer.hpp"
#include "mesh.hpp"
#include "droneManager.hpp"
// Libs
#include "mat4x4.hpp"

class Engine {
 private:
  Vector<int> windowSize_;
  RenderEngine* renderer_;
  ComputeShaderCompiler* computeShaderCompiler_;
  Camera* camera_;
  Vector<int> mousePosition_;

  // TEMP
  std::vector<RenderData*>* renderData_;

  // Compute shaders
  std::map<std::string, ComputeShader*>* computeShaders_;
  std::map<std::string, ComputeShaderBuffer*>* computeShaderBuffers_;

  void MoveCamera() noexcept;
  void CalculateMousePosition() noexcept;

  // Simulation stuff
  DroneManager* droneManager_;

 public:
  Engine(const Vector<int>& windowSize, const std::string& name);
  ~Engine();

  // Utility
  void Start();
  void CompileComputeShader(const std::string& computeFile,
                            const std::string& name);
  ComputeShaderBuffer* const AssignNewComputeShaderBuffer(
      const std::string& name, const unsigned int& width,
      const unsigned int& height) const;
  Drone* AddDrone(Drone* drone) const noexcept;
  Drone* AddDrone(Drone* drone, const std::string& tag) const noexcept;

  // Getters
  RenderEngine* const GetRenderer() const noexcept;
  Vector<int> GetWindowSize() const noexcept;
  DroneManager* const GetDroneManager() const noexcept;
  Vector<int> GetMousePosition() const noexcept;
  ComputeShader* const GetComputeShader(const std::string& name) const;
  ComputeShaderBuffer* const GetComputeShaderBuffer(
      const std::string& name) const noexcept;
};
#endif  // ENGINE_HPP_