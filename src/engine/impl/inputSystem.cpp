#include "inputSystem.hpp"

InputSystem::InputSystem(const Vector<int>& windowSize)
    : windowSize_(windowSize) {}

InputSystem::~InputSystem() {}

// Utility
void InputSystem::Update(GLFWwindow* const window) noexcept {
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  this->mousePosition_ = Vector<float>(xpos, this->windowSize_.y - ypos);
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    this->isMouseDown_ = true;
  } else {
    this->isMouseDown_ = false;
  }

  //* Events
  // Direction Event
  Vector<float> direction;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    direction.y = -1.0f;
  } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    direction.y = 1.0f;
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    direction.x = 1.0f;
  } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    direction.x = -1.0f;
  }
  if (direction.x != 0.0f && direction.y != 0.0f) {
    direction.x *= 0.70710678118f;  // sqrt(2)/2
    direction.y *= 0.70710678118f;
  }
  for (auto& directionCallback : this->directionUpdateEvents_) {
    directionCallback.func(directionCallback.object, direction);
  }

  // Key Press Events
  for (auto& event : this->keyPressEvents_) {
    if (glfwGetKey(window, event.first) == GLFW_PRESS) {
      for (auto& keyCallback : event.second) {
        keyCallback.func(keyCallback.object);
      }
    }
  }
}

// Events
void InputSystem::AssignOnDirectionUpdate(DirectionCallback callback) noexcept {
  this->directionUpdateEvents_.push_back(callback);
}

void InputSystem::AssignOnKeyPress(int key, KeyCallback callback) noexcept {
  if (this->keyPressEvents_.count(key) == 0) {
    this->keyPressEvents_.insert(std::pair<int, std::vector<KeyCallback>>(
        key, std::vector<KeyCallback>()));
  }
  this->keyPressEvents_.at(key).push_back(callback);
}

// Getters
Vector<float> InputSystem::GetMousePosition() const noexcept {
  return this->mousePosition_;
}

bool InputSystem::IsMouseDown() const noexcept { return this->isMouseDown_; }
