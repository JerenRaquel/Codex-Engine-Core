#include "../headers/droneManager.hpp"

#include "../../../tools/tracy/tracy/Tracy.hpp"

DroneManager::DroneManager(Engine* const engine) {
  this->engineRef_ = engine;
  this->allDrones_ = new std::vector<DroneData*>();
  this->droneMap_ = new std::map<std::string, std::vector<DroneData*>*>();
  this->positionMap_ =
      new std::map<std::string, std::vector<Vector<float>*>*>();
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

  for (auto pair : *this->positionMap_) {
    for (Vector<float>* position : *pair.second) {
      delete position;
    }
    delete pair.second;
  }
  delete this->positionMap_;
}

// Utility
void DroneManager::OnStart() const noexcept {
  for (auto pair : *this->droneMap_) {
    for (unsigned int i = 0; i < pair.second->size(); i++) {
      DroneData* droneData = pair.second->at(i);
      droneData->drone->OnStart(this->engineRef_, droneData->tag,
                                droneData->id);
    }
  }
}

void DroneManager::OnUpdate() const noexcept {
  ZoneScopedN("Engine::DroneUpdates");
  for (auto pair : *this->droneMap_) {
    for (unsigned int i = 0; i < pair.second->size(); i++) {
      DroneData* droneData = pair.second->at(i);
      droneData->drone->OnUpdate(this->engineRef_, droneData->tag,
                                 droneData->id);
    }
  }
}

DroneManager* const DroneManager::AddDrone(Drone* drone,
                                           const std::string& tag) {
  // std::transform(tag.begin(), tag.end(), tag.begin(),
  //                [](unsigned char c) { return std::tolower(c); });
  if (tag == "all") {
    throw std::runtime_error("Tag is a reserved drone tag.");
  }

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

  if (this->positionMap_->count(tag) == 0) {
    this->positionMap_->insert(
        std::pair<std::string, std::vector<Vector<float>*>*>(
            tag, new std::vector<Vector<float>*>()));
  }
  this->positionMap_->at(tag)->push_back(drone->GetPosition());

  return this;
}

// Getters - Entity
DroneData* const DroneManager::GetClosestDrone(
    std::vector<DroneData*>* drones,
    const Vector<float>& position) const noexcept {
  float minDistance = std::numeric_limits<float>::max();
  DroneData* closestDrone = nullptr;
  for (DroneData* droneData : *drones) {
    float distance = position.SqrDistance(*(droneData->drone->GetPosition()));
    if (distance < minDistance) {
      minDistance = distance;
      closestDrone = droneData;
    }
  }
  return closestDrone;
}

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

std::vector<Vector3<float>>* const DroneManager::GetDroneDistancesByTag(
    const std::string& tag, const Vector<float>& position) const noexcept {
  ComputeShader* computeShader =
      this->engineRef_->GetComputeShader("CalulateDistances");
  ComputeShaderBuffer* computeShaderBuffer =
      this->engineRef_->GetComputeShaderBuffer("DroneDistances");

  std::vector<Vector<float>*>* positions = this->GetTaggedPositions(tag);
  unsigned int droneCount = positions->size();
  float* data = new float[3 * droneCount];
  for (unsigned int i = 0; i < droneCount; i++) {
    data[i * 3] = positions->at(i)->x;
    data[i * 3 + 1] = positions->at(i)->y;
    data[i * 3 + 2] = 0.0f;
  }

  if (computeShaderBuffer == nullptr) {
    computeShaderBuffer = this->engineRef_->AssignNewComputeShaderBuffer(
        "DroneDistances", droneCount, 1);

    computeShaderBuffer->CreateBuffer(sizeof(float) * 3 * droneCount, data);
  } else {
    computeShaderBuffer->UpdateBuffer(sizeof(float) * 3 * droneCount, data);
  }

  computeShader->BindDataBufferAndUse(computeShaderBuffer);
  computeShader->PassUniform2f("position", position);
  computeShader->DispatchAndWait(computeShaderBuffer);
  computeShaderBuffer->ReadBuffer(sizeof(float) * 3 * droneCount, data);

  std::vector<Vector3<float>>* distances = new std::vector<Vector3<float>>();
  distances->resize(droneCount);
  for (unsigned int i = 0; i < droneCount; i++) {
    distances->at(i) =
        Vector3<float>(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
  };
  delete data;
  return distances;
}

// Getters - Component
std::vector<Vector<float>*>* const DroneManager::GetAllPositions()
    const noexcept {
  std::vector<Vector<float>*>* positions = new std::vector<Vector<float>*>();
  for (DroneData* droneData : *this->allDrones_) {
    positions->push_back(droneData->drone->GetPosition());
  }

  return positions;
}

std::vector<Vector<float>*>* const DroneManager::GetTaggedPositions(
    const std::string& tag) const noexcept {
  if (this->positionMap_->count(tag) == 0) {
    return nullptr;
  } else {
    return this->positionMap_->at(tag);
  }
}
