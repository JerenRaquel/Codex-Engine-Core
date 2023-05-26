#ifndef DRONEMANAGER_HPP_
#define DRONEMANAGER_HPP_

// Std
#include <map>
#include <string>
#include <vector>
// Custom
#include "drone.hpp"

struct DroneData {
  std::string tag;
  unsigned int id;
  Drone* drone;
};

class DroneManager {
 private:
  std::vector<DroneData*>* allDrones_;
  std::map<std::string, std::vector<DroneData*>*>* droneMap_;

 public:
  DroneManager();
  ~DroneManager();

  // Utility
  void OnStart(Engine* const engine) const noexcept;
  void OnUpdate(Engine* const engine) const noexcept;
  DroneManager* const AddDrone(Drone* drone, const std::string& tag) noexcept;
  std::vector<DroneData*>* const FilterBasedOnRange(
      std::vector<DroneData*>* drones, const Vector<float>& position,
      const float& range) const noexcept;
  std::vector<DroneData*>* const FilterBasedOnRange(
      std::vector<DroneData*>* drones, const Vector<float>& position,
      const float& range, const unsigned int& successLimit) const noexcept;
  // Getters
  std::vector<DroneData*>* const GetAllDrones() const noexcept;
  unsigned int GetAllDroneCount() const noexcept;
  std::vector<DroneData*>* const GetDronesByTag(
      const std::string& tag) const noexcept;
  unsigned int GetDroneCountByTag(const std::string& tag) const noexcept;
  Drone* const GetDroneByTagId(const std::string& tag,
                               unsigned int id) const noexcept;
};
#endif  // DRONEMANAGER_HPP_