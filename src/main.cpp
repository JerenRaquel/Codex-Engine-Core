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
    engine->GetRenderer()
        ->AddQuad(new Quad(Vector<float>(5, 5)))
        ->SetScale(Vector<float>(10.0f, 10.0f))
        ->SetPosition(Vector<float>(engine->GetWindowSize().x / 2.0f,
                                    engine->GetWindowSize().y / 2.0f))
        ->SetColor(1.0f, 0.0f, 0.0f);
  });

  engine->Start();
  delete engine;

  return 0;
}
