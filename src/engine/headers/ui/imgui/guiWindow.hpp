#ifndef GUIWINDOW_HPP_
#define GUIWINDOW_HPP_

// ImGUI
#include <imgui.h>
// Std
#include <string>
// Engine
#include "engine.hpp"

class GuiWindow {
 private:
  std::string name_;
  void (*callback_)(void) = nullptr;

 public:
  GuiWindow(std::string name, void (*callback)(void));
  ~GuiWindow();

  void Display() noexcept;
  std::string GetName() const noexcept;
};
#endif  // GUIWINDOW_HPP_