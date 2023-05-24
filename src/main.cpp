/*	Jeren Raquel
 *	==Project Name==
 *	Description
 */
// Custom
#include "engine/headers/engine.hpp"

int main(int argc, char** argv) {
  Vector<int> size(900, 640);

  Engine* engine = new Engine(size, "Hello World");

  engine->AddStartFunction([](Engine* const engine) {
    float vertices[] = {
        -2.5f, -2.5f, 0.0f,  // top left
        2.5f,  -2.5f, 0.0f,  // top right
        2.5f,  2.5f,  0.0f,  // bottom right
        -2.5f, 2.5f,  0.0f   // bottom left
    };
    unsigned int indices[] = {
        0, 1, 2,  // first triangle
        2, 3, 0   // second triangle
    };

    engine->GetRenderer()
        ->AddMesh(new Mesh(vertices, 12, indices, 6))
        ->SetScale(Vector<float>(10.0f, 10.0f))
        ->SetPosition(Vector<float>(engine->GetWindowSize().x / 2.0f,
                                    engine->GetWindowSize().y / 2.0f))
        ->SetColor(1.0f, 0.0f, 0.0f);
  });

  engine->Start();
  delete engine;

  return 0;
}
