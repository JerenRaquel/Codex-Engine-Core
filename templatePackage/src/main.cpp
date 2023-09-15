/*	Jeren Raquel
 *	==Name==
 *	Description
 */
// Std
#include <cstdlib>
#include <vector>
// Engine
#include "engine.hpp"
#include "globalAction.hpp"

int main(int argc, char** argv) {
  // Pack args into vector
  std::vector<std::string> args;
  for (int i = 1; i < argc; i++) {
    args.push_back(argv[i]);
  }

  // Start engine
  GlobalAction* action = new GlobalAction();
  Engine* engine =
      new Engine(Vector2<int>(1600, 900), "Codex Engine", args, action);
  delete engine;

  return 0;
}
