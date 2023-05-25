#include "../headers/droneManager.hpp"

#include "../../../tools/tracy/tracy/Tracy.hpp"

DroneManager::DroneManager() {
  this->allDrones_ = new std::vector<DroneData*>();
  this->droneMap_ = new std::map<std::string, std::vector<DroneData*>*>();
}

DroneManager::~DroneManager() {
  for (DroneData* droneData : *this->allDrones_) {
    delete droneData->drone;
    delete droneData;
  }
  delete this->allDrones_;

  for (auto pair : *this->droneMap_) {
    delete pair.second;
  }
  delete this->droneMap_;
}

// Utility
void DroneManager::OnStart(Engine* const engine) const noexcept {
  for (auto pair : *this->droneMap_) {
    for (unsigned int i = 0; i < pair.second->size(); i++) {
      DroneData* droneData = pair.second->at(i);
      droneData->drone->OnStart(engine, droneData->tag, droneData->id);
    }
  }
}

void DroneManager::OnUpdate(Engine* const engine) const noexcept {
  ZoneScopedN("Engine::DroneUpdates");
  for (auto pair : *this->droneMap_) {
    for (unsigned int i = 0; i < pair.second->size(); i++) {
      DroneData* droneData = pair.second->at(i);
      droneData->drone->OnUpdate(engine, droneData->tag, droneData->id);
    }
  }
}

DroneManager* const DroneManager::AddDrone(Drone* drone,
                                           const std::string& tag) noexcept {
  if (this->droneMap_->count(tag) == 0) {
    this->droneMap_->insert(std::pair<std::string, std::vector<DroneData*>*>(
        tag, new std::vector<DroneData*>()));
  }

  DroneData* droneData = new DroneData();
  droneData->tag = tag;
  droneData->id = this->droneMap_->at(tag)->size();
  droneData->drone = drone;
  this->droneMap_->at(tag)->push_back(droneData);
  this->allDrones_->push_back(droneData);

  return this;
}

std::vector<DroneData*>* const DroneManager::FilterBasedOnRange(
    std::vector<DroneData*>* drones, const Vector<float>& position,
    const float& range) const noexcept {
  ZoneScopedN("DroneManager::FilterBasedOnRange");
  std::vector<DroneData*>* resultingDrones = new std::vector<DroneData*>();

  for (DroneData* droneData : *drones) {
    if (droneData->drone->GetMesh()->GetPosition().IsWithinSqrDistance(position,
                                                                       range)) {
      resultingDrones->push_back(droneData);
    }
  }

  return resultingDrones;
}

void DroneManager::CleanDroneData(
    std::vector<DroneData*>* const droneData) const noexcept {
  ZoneScopedN("DroneManager::CleanDroneData");
  for (DroneData* droneDat : *droneData) {
    delete droneDat;
  }
  delete droneData;
}

// Getters
std::vector<DroneData*>* const DroneManager::GetAllDrones() const noexcept {
  return this->allDrones_;
}

unsigned int DroneManager::GetAllDroneCount() const noexcept {
  return this->allDrones_->size();
}

std::vector<DroneData*>* const DroneManager::GetDronesByTag(
    const std::string& tag) const noexcept {
  if (this->droneMap_->count(tag) == 0) {
    return nullptr;
  }
  return this->droneMap_->at(tag);
}

unsigned int DroneManager::GetDroneCountByTag(
    const std::string& tag) const noexcept {
  if (this->droneMap_->count(tag) == 0) {
    return 0;
  }
  return this->droneMap_->at(tag)->size();
}

Drone* const DroneManager::GetDroneByTagId(const std::string& tag,
                                           unsigned int id) const noexcept {
  if (this->droneMap_->count(tag) == 0) {
    return nullptr;
  }
  if (this->droneMap_->at(tag)->size() <= id) {
    return nullptr;
  }

  return this->droneMap_->at(tag)->at(id)->drone;
}
