#ifndef DRONE_HPP_
#define DRONE_HPP_

// Std
#include <string>
// Custom
#include "../../engine/headers/mesh.hpp"
#include "../../engine/headers/vector.hpp"

class DroneManager;

class Drone {
 private:
  Mesh* mesh_;
  void (*startFunc_)(DroneManager* const droneManager, Drone* const drone,
                     const std::string& tag, const unsigned int id) = nullptr;
  void (*updateFunc_)(DroneManager* const droneManager, Drone* const drone,
                      const std::string& tag, const unsigned int id) = nullptr;

 public:
  Drone(Vector<float> position, Vector<float> scale);
  Drone(Vector<float> position, Vector<float> scale, Vector3<float> color);
  ~Drone();

  // Utility
  void OnStart(DroneManager* const droneManager, const std::string& tag,
               const unsigned int id) const noexcept;
  void OnUpdate(DroneManager* const droneManager, const std::string& tag,
                const unsigned int id) const noexcept;
  Drone* const AssignStartFunction(
      void (*func)(DroneManager* const droneManager, Drone* const self,
                   const std::string& tag, const unsigned int id)) noexcept;
  Drone* const AssignUpdateFunction(
      void (*func)(DroneManager* const droneManager, Drone* const self,
                   const std::string& tag, const unsigned int id)) noexcept;
  // Getters
  Mesh* const GetMesh() const noexcept;
};
#endif  // DRONE_HPP_