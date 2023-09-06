#ifndef GUIMANAGER_HPP_
#define GUIMANAGER_HPP_

// ImGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GuiManager {
 private:
  ImGuiIO* io_ = nullptr;

 public:
  GuiManager(GLFWwindow* window);
  ~GuiManager();

  void NewFrame() const noexcept;
  void Display() const noexcept;
  void Render() const noexcept;
};
#endif  // GUIMANAGER_HPP_