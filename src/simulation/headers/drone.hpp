#ifndef DRONE_HPP_
#define DRONE_HPP_

// Std
#include <string>
// Custom
#include "../../engine/headers/mesh.hpp"
#include "../../engine/headers/vector.hpp"
#include "../../engine/headers/engine.hpp"

// Based Class
class Drone {
 protected:
  Mesh* mesh_;
  virtual void InternalStart(Engine* const engine, const std::string& tag,
                             const unsigned int id) = 0;
  virtual void InternalUpdate(Engine* const engine, const std::string& tag,
                              const unsigned int id) = 0;

 public:
  Drone(Vector<float> position, Vector<float> scale);
  Drone(Vector<float> position, Vector<float> scale, Vector3<float> color);
  virtual ~Drone();

  // Utility
  void OnStart(Engine* const engine, const std::string& tag,
               const unsigned int id) noexcept;
  void OnUpdate(Engine* const engine, const std::string& tag,
                const unsigned int id) noexcept;
  // Getters
  Mesh* const GetMesh() const noexcept;
};
#endif  // DRONE_HPP_