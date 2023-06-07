/*	Jeren Raquel
 *	==Drone Simulation==
 *	Description
 */
// Std
#include <cstdlib>
#include <vector>
// Engine
#include "engine.hpp"
// Simulation
#include "testAction.hpp"

int main(int argc, char** argv) {
  // Pack args into vector
  std::vector<std::string> args;
  for (int i = 1; i < argc; i++) {
    args.push_back(argv[i]);
  }

  // Start engine
  Engine* engine = new Engine(Vector<int>(1600, 900), "Drone Simulation", args);
  engine->AddAction(new TestAction());
  engine->Start();
  delete engine;

  return 0;
}
