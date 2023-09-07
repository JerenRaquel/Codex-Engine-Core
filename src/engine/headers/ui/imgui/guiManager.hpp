#ifndef GUIMANAGER_HPP_
#define GUIMANAGER_HPP_

class GuiWindow;

// ImGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Engine
#include "guiWindow.hpp"
// Std
#include <map>

class GuiManager {
 private:
  ImGuiIO* io_ = nullptr;
  std::map<std::string, GuiWindow*>* guiWindows_ = nullptr;

 public:
  GuiManager(GLFWwindow* window);
  ~GuiManager();

  void NewFrame() const noexcept;
  void Display() const noexcept;
  void Render() const noexcept;

  void AddWindow(GuiWindow* const guiWindow) noexcept;
  void RemoveWindow(const std::string& name);
};
#endif  // GUIMANAGER_HPP_