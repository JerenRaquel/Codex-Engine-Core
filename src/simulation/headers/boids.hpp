#ifndef BOIDS_HPP_
#define BOIDS_HPP_

// Std
#include <string>
#include <vector>
// Custom
#include "drone.hpp"

class Boids : public Drone {
 private:
  // Base Class
  void InternalUpdate(Engine* const engine, const std::string& tag,
                      const unsigned int id) override;

  // Member Data
  float targetBias = 0.03f;
  float cohesionBias = 0.02f;
  float separationBias = 0.01f;
  float flySpeed = 5.0f;
  void Avoidance(std::vector<Vector<float>*>* positions) const noexcept;
  void Cohesion(std::vector<Vector<float>*>* positions) const noexcept;
  void Move() const noexcept;

 public:
  Boids(Vector<float>* position, Vector<float> scale);
  Boids(Vector<float>* position, Vector<float> scale, Vector3<float> color);
  ~Boids();
};
#endif  // BOIDS_HPP_