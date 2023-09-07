#include "ui/imgui/guiWindow.hpp"

GuiWindow::GuiWindow(std::string name, void (*callback)(void))
    : name_(name), callback_(callback) {}

GuiWindow::~GuiWindow() {}

void GuiWindow::Display() noexcept {
  ImGui::Begin(this->name_.c_str());
  this->callback_();
  ImGui::End();
}

std::string GuiWindow::GetName() const noexcept { return this->name_; }
