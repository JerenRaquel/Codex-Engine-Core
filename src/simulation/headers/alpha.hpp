#ifndef ALPHA_HPP_
#define ALPHA_HPP_

// Custom
#include "drone.hpp"

class Alpha : public Drone {
 private:
  // Base Class
  void InternalStart(Engine* const engine, const std::string& tag,
                     const unsigned int id) override;
  void InternalUpdate(Engine* const engine, const std::string& tag,
                      const unsigned int id) override;

  // Member Data
  float targetBias = 0.05f;
  float separationBias = 0.1f;
  float flySpeed = 5.0f;
  void Move() const noexcept;
  void Avoidance(const std::vector<DroneData*>* const drones,
                 const unsigned int& selfID) const noexcept;

 public:
  Alpha(Vector<float> position, Vector<float> scale);
  Alpha(Vector<float> position, Vector<float> scale, Vector3<float> color);
  ~Alpha();
};
#endif  // ALPHA_HPP_