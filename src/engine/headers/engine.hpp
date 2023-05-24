#ifndef ENGINE_HPP_
#define ENGINE_HPP_

// Std
#include <string>
#include <vector>
// Custom
#include "vector.hpp"
#include "renderEngine.hpp"
#include "camera.hpp"

// Simulation
#include "../../simulation/headers/drone.hpp"
#include "../../simulation/headers/droneManager.hpp"

class Engine {
 private:
  Vector<int> windowSize_;
  RenderEngine* renderer_;
  Camera* camera_;

  void MoveCamera() noexcept;

  // Simulation stuff
  DroneManager* droneManager_;

 public:
  Engine(const Vector<int>& windowSize, const std::string& name);
  ~Engine();

  void Start();
  Drone* AddDrone(Drone* drone) const noexcept;
  Drone* AddDrone(Drone* drone, const std::string& tag) const noexcept;

  // Getters
  RenderEngine* const GetRenderer() const noexcept;
  Vector<int> GetWindowSize() const noexcept;
  DroneManager* const GetDroneManager() const noexcept;
};
#endif  // ENGINE_HPP_