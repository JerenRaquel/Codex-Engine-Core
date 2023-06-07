#ifndef DRONE_HPP_
#define DRONE_HPP_

// Std
#include <string>
// Custom
#include "mesh.hpp"
#include "vector.hpp"
#include "engine.hpp"
#include "material.hpp"
#include "transform.hpp"

// Based Class
class Drone {
 protected:
  Material* material_;
  Transform* transform_;

  virtual void InternalStart(Engine* const engine, const std::string& tag,
                             const unsigned int id) = 0;
  virtual void InternalUpdate(Engine* const engine, const std::string& tag,
                              const unsigned int id) = 0;

 public:
  Drone(Vector<float>* position, Vector<float> scale);
  Drone(Vector<float>* position, Vector<float> scale, Vector3<float> color);
  virtual ~Drone();

  // Utility
  void OnStart(Engine* const engine, const std::string& tag,
               const unsigned int id) noexcept;
  void OnUpdate(Engine* const engine, const std::string& tag,
                const unsigned int id) noexcept;
  // Getters
  Material* const GetMaterial() const noexcept;
  Transform* const GetTransform() const noexcept;
  Vector<float>* const GetPosition() const noexcept;
};
#endif  // DRONE_HPP_