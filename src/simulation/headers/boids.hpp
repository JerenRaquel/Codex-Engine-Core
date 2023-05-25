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
  void InternalStart(Engine* const engine, const std::string& tag,
                     const unsigned int id) override;
  void InternalUpdate(Engine* const engine, const std::string& tag,
                      const unsigned int id) override;

  // Member Data
  float targetBias = 0.05f;
  float cohesionBias = 0.02f;
  float separationBias = 0.01f;
  float flySpeed = 5.0f;
  void FlyTowardsCenter(const Vector<float>& center) const noexcept;
  void CohesionAndAvoidance(
      const std::vector<DroneData*>* const drones) const noexcept;
  void Move() const noexcept;
  void BlendColors(const std::vector<DroneData*>* const drones,
                   unsigned int selfID) const noexcept;

 public:
  Boids(Vector<float> position, Vector<float> scale);
  Boids(Vector<float> position, Vector<float> scale, Vector3<float> color);
  ~Boids();
};
#endif  // BOIDS_HPP_