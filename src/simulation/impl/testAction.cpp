#include "testAction.hpp"

// Base Class
void TestAction::InternalStart(const Engine* const engine) const noexcept {
  engine->CompileComputeShader("CalulateDistances.comp", "CalulateDistances");

  float vertices[] = {
      0.0f,  2.5f,  0.0f,  // top center
      -2.5f, -2.5f, 0.0f,  // bottom left
      2.5f,  -2.5f, 0.0f,  // bottom right
  };
  unsigned int indices[] = {
      0, 1, 2,  // first triangle
  };

  Mesh* droneMesh = new Mesh(vertices, 9, indices, 3);
  engine->GetRenderer()->AddMeshType("drone", droneMesh);
}

void TestAction::InternalUpdate(const Engine* const engine) const noexcept {
  engine->GetRenderer()->DrawText("hello world", Vector<int>(10.0f, 450.0f), 1);
}

TestAction::TestAction() : Action() {}

TestAction::~TestAction() {}
