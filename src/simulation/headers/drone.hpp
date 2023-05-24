#ifndef DRONE_HPP_
#define DRONE_HPP_

// Custom
#include "../../engine/headers/mesh.hpp"
#include "../../engine/headers/vector.hpp"

class Drone {
 private:
  Mesh* mesh_;

 public:
  Drone(Vector<float> position, Vector<float> scale, Vector3<float> color);
  ~Drone();

  // Getters
  Mesh* const GetMesh() const noexcept;
};
#endif  // DRONE_HPP_