#include "../headers/droneManager.hpp"

DroneManager::DroneManager() {
  this->allDrones_ = new std::vector<Drone*>();
  this->droneMap_ = new std::map<std::string, std::vector<Drone*>*>();
}

DroneManager::~DroneManager() {
  for (auto drone : *this->allDrones_) {
    delete drone;
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
      pair.second->at(i)->OnStart(engine, pair.first, i);
    }
  }
}

void DroneManager::OnUpdate(Engine* const engine) const noexcept {
  for (auto pair : *this->droneMap_) {
    for (unsigned int i = 0; i < pair.second->size(); i++) {
      pair.second->at(i)->OnUpdate(engine, pair.first, i);
    }
  }
}

DroneManager* const DroneManager::AddDrone(Drone* drone,
                                           const std::string& tag) noexcept {
  this->allDrones_->push_back(drone);
  if (this->droneMap_->count(tag) == 0) {
    this->droneMap_->insert(std::pair<std::string, std::vector<Drone*>*>(
        tag, new std::vector<Drone*>()));
  }
  this->droneMap_->at(tag)->push_back(drone);
  return this;
}

// Getters
std::vector<Drone*>* const DroneManager::GetAllDrones() const noexcept {
  return this->allDrones_;
}

std::vector<Drone*>* const DroneManager::GetDronesByTag(
    std::string tag) const noexcept {
  if (this->droneMap_->count(tag) == 0) {
    return nullptr;
  }
  return this->droneMap_->at(tag);
}

Drone* const DroneManager::GetDroneByTagId(std::string tag,
                                           unsigned int id) const noexcept {
  if (this->droneMap_->count(tag) == 0) {
    return nullptr;
  }
  if (this->droneMap_->at(tag)->size() <= id) {
    return nullptr;
  }

  return this->droneMap_->at(tag)->at(id);
}
