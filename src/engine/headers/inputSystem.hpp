#ifndef INPUTSYSTEM_HPP_
#define INPUTSYSTEM_HPP_

// Std
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
// Engine
#include "renderEngine.hpp"  // Includes GLFW
#include "util/vector3.hpp"

class InputSystem {
 public:
  struct DirectionCallback {
    void* object;
    void (*func)(void* object, const Vector2<float>& direction);
  };
  struct KeyCallback {
    void* object;
    void (*func)(void* object);
  };

 private:
  Engine* engine_;
  std::map<std::string, DirectionCallback> directionUpdateEvents_;
  std::map<int, std::map<std::string, KeyCallback>> keyPressEvents_;

  // Mouse Data
  Vector2<float> mousePosition_;
  bool isMouseDown_ = false;

 public:
  InputSystem(Engine* const engine);
  ~InputSystem();

  // Utility
  void Update() noexcept;

  // Events
  std::string AssignOnDirectionUpdate(DirectionCallback callback) noexcept;
  std::string AssignOnKeyPress(int key, KeyCallback callback) noexcept;
  void UnassignOnDirectionUpdate(std::string uuid) noexcept;
  void UnassignOnKeyPress(int key, std::string uuid) noexcept;

  // Getters
  Vector2<float> GetMousePosition() const noexcept;
  bool IsMouseDown() const noexcept;
};
#endif  // INPUTSYSTEM_HPP_