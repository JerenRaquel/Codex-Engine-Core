#ifndef DRONEMANAGER_HPP_
#define DRONEMANAGER_HPP_

// Std
#include <map>
#include <string>
#include <vector>
#include <algorithm>
// Custom
#include "drone.hpp"
#include "../../engine/headers/computeShader.hpp"
#include "../../engine/headers/computeShaderBuffer.hpp"
#include "../../engine/headers/dataStream.hpp"

struct DroneData {
  std::string tag;
  unsigned int id;
  Drone* drone;
};

class DroneManager {
 private:
  Engine* engineRef_;

  // Entities
  std::vector<DroneData*>* allDrones_;
  std::map<std::string, std::vector<DroneData*>*>* droneMap_;

  //* Components
  // <tag, position>
  std::map<std::string, std::vector<Vector<float>*>*>* positionMap_;
  // std::map<std::string, Vector3<float>*>* colorMap_;

 public:
  DroneManager(Engine* const engine);
  ~DroneManager();

  // Utility
  void OnStart() const noexcept;
  void OnUpdate() const noexcept;
  DroneManager* const AddDrone(Drone* drone, const std::string& tag);

  // Getters - Entity
  DroneData* const GetClosestDrone(
      std::vector<DroneData*>* drones,
      const Vector<float>& position) const noexcept;
  std::vector<DroneData*>* const GetAllDrones() const noexcept;
  unsigned int GetAllDroneCount() const noexcept;
  std::vector<DroneData*>* const GetDronesByTag(
      const std::string& tag) const noexcept;
  unsigned int GetDroneCountByTag(const std::string& tag) const noexcept;
  Drone* const GetDroneByTagId(const std::string& tag,
                               unsigned int id) const noexcept;
  std::vector<Vector3<float>>* const GetDroneDistancesByTag(
      const std::string& tag, const Vector<float>& position) const noexcept;

  // Getters - Component
  std::vector<Vector<float>*>* const GetAllPositions() const noexcept;
  std::vector<Vector<float>*>* const GetTaggedPositions(
      const std::string& tag) const noexcept;
};
#endif  // DRONEMANAGER_HPP_