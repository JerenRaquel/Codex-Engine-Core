#include "inputSystem.hpp"

InputSystem::InputSystem(Engine* const engine) : engine_(engine) {}

InputSystem::~InputSystem() {}

// Utility
void InputSystem::Update() noexcept {
  GLFWwindow* window = this->engine_->GetRenderer()->GetWindow();
  Vector2<int> windowSize = this->engine_->GetWindowSize();

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  this->mousePosition_ = Vector2<float>(xpos, windowSize.y - ypos);
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    this->isMouseDown_ = true;
  } else {
    this->isMouseDown_ = false;
  }

  //* Events
  // Direction Event
  Vector2<float> direction;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    direction.y = 1.0f;
  } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    direction.y = -1.0f;
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    direction.x = -1.0f;
  } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    direction.x = 1.0f;
  }
  if (direction.x != 0.0f && direction.y != 0.0f) {
    direction.x *= 0.70710678118f;  // sqrt(2)/2
    direction.y *= 0.70710678118f;
  }
  for (auto& directionCallback : this->directionUpdateEvents_) {
    directionCallback.second.func(directionCallback.second.object, direction);
  }

  // Key Press Events
  for (auto& event : this->keyPressEvents_) {
    if (glfwGetKey(window, event.first) == GLFW_PRESS) {
      for (auto& keyCallback : event.second) {
        keyCallback.second.func(keyCallback.second.object);
      }
    }
  }
}

// Events
std::string InputSystem::AssignOnDirectionUpdate(
    DirectionCallback callback) noexcept {
  std::string uuid = this->engine_->GenerateUUID();
  this->directionUpdateEvents_.insert(
      std::pair<std::string, DirectionCallback>(uuid, callback));
  return uuid;
}

std::string InputSystem::AssignOnKeyPress(int key,
                                          KeyCallback callback) noexcept {
  if (this->keyPressEvents_.count(key) == 0) {
    this->keyPressEvents_.insert(
        std::pair<int, std::map<std::string, KeyCallback>>(
            key, std::map<std::string, KeyCallback>()));
  }

  std::string uuid = this->engine_->GenerateUUID();
  this->keyPressEvents_.at(key).insert(
      std::pair<std::string, KeyCallback>(uuid, callback));
  return uuid;
}

void InputSystem::UnassignOnDirectionUpdate(std::string uuid) noexcept {
  if (this->directionUpdateEvents_.count(uuid) == 0) {
    return;
  }
  this->directionUpdateEvents_.erase(uuid);
}

void InputSystem::UnassignOnKeyPress(int key, std::string uuid) noexcept {
  if (this->keyPressEvents_.count(key) == 0) {
    return;
  }
  if (this->keyPressEvents_.at(key).count(uuid) == 0) {
    return;
  }
  this->keyPressEvents_.at(key).erase(uuid);
}

// Getters
Vector2<float> InputSystem::GetMousePosition() const noexcept {
  return this->mousePosition_;
}

bool InputSystem::IsMouseDown() const noexcept { return this->isMouseDown_; }
