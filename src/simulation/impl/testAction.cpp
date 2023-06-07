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

  int droneCount = 1000;
  if ((*(engine->GetArgs())).size() > 0) {
    droneCount = std::atoi((*(engine->GetArgs()))[0].c_str());
  }
  for (int i = 0; i < droneCount; i++) {
    Vector<float>* position =
        new Vector<float>(std::rand() % engine->GetWindowSize().x,
                          std::rand() % engine->GetWindowSize().y);
    engine->AddDrone(new Boids(position, Vector<float>(2.5f, 2.5f)), "Boids");
  }

  for (unsigned int i = 0; i < 10; i++) {
    Vector<float>* position =
        new Vector<float>(std::rand() % engine->GetWindowSize().x,
                          std::rand() % engine->GetWindowSize().y);
    engine->AddDrone(new Alpha(position, Vector<float>(10.0f, 10.0f)), "Alpha");
  }
}

void TestAction::InternalUpdate(const Engine* const engine) const noexcept {
  engine->GetRenderer()->DrawText("hello world", Vector<int>(10.0f, 450.0f), 1);
}

TestAction::TestAction() : Action() {}

TestAction::~TestAction() {}
