#ifndef DRONE_HPP_
#define DRONE_HPP_

// Std
#include <string>
// Custom
#include "../../engine/headers/mesh.hpp"
#include "../../engine/headers/vector.hpp"

class Engine;

class Drone {
 private:
  Mesh* mesh_;
  void (*startFunc_)(Engine* const engine, Drone* const drone,
                     const std::string& tag, const unsigned int id) = nullptr;
  void (*updateFunc_)(Engine* const engine, Drone* const drone,
                      const std::string& tag, const unsigned int id) = nullptr;

 public:
  Drone(Vector<float> position, Vector<float> scale);
  Drone(Vector<float> position, Vector<float> scale, Vector3<float> color);
  ~Drone();

  // Utility
  void OnStart(Engine* const engine, const std::string& tag,
               const unsigned int id) const noexcept;
  void OnUpdate(Engine* const engine, const std::string& tag,
                const unsigned int id) const noexcept;
  Drone* const AssignStartFunction(
      void (*func)(Engine* const engine, Drone* const self,
                   const std::string& tag, const unsigned int id)) noexcept;
  Drone* const AssignUpdateFunction(
      void (*func)(Engine* const engine, Drone* const self,
                   const std::string& tag, const unsigned int id)) noexcept;
  // Getters
  Mesh* const GetMesh() const noexcept;
};
#endif  // DRONE_HPP_