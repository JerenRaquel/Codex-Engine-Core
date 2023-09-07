#include "../headers/ui/guiManager.hpp"

GuiManager::GuiManager(GLFWwindow* window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  this->io_ = &ImGui::GetIO();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 450");

  this->guiWindows_ = new std::map<std::string, GuiWindow*>();
}

GuiManager::~GuiManager() {
  for (auto& guiWindow : *this->guiWindows_) {
    delete guiWindow.second;
  }
  delete this->guiWindows_;

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
  for (auto& guiWindow : *this->guiWindows_) {
    guiWindow.second->Display();
  }
}

void GuiManager::Render() const noexcept {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiManager::AddWindow(GuiWindow* const guiWindow) noexcept {
  this->guiWindows_->insert(
      std::pair<std::string, GuiWindow*>(guiWindow->GetName(), guiWindow));
}

void GuiManager::RemoveWindow(const std::string& name) {
  if (this->guiWindows_->count(name) == 0) {
    throw std::runtime_error("ERROR: Window with name " + name +
                             " does not exist!");
  }
  this->guiWindows_->erase(name);
}
