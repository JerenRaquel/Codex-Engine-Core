/*	Jeren Raquel
 *	==Project Name==
 *	Description
 */
// Custom
#include "engine/headers/engine.hpp"

int main(int argc, char** argv) {
  Vector<int> size(900, 640);

  Engine* engine = new Engine(size, "Hello World");
  engine->Start();
  delete engine;

  return 0;
}
