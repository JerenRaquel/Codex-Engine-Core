#include "../headers/ui/guiManager.hpp"

GuiManager::GuiManager(GLFWwindow* window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  this->io_ = &ImGui::GetIO();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 450");
}

GuiManager::~GuiManager() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void GuiManager::NewFrame() const noexcept {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void GuiManager::Display() const noexcept {
  ImGui::Begin("Hello, world!");
  ImGui::Text("This is some useful text.");
  ImGui::End();
}

void GuiManager::Render() const noexcept {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
