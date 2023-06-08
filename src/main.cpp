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
#include "mainAction.hpp"

int main(int argc, char** argv) {
  // Pack args into vector
  std::vector<std::string> args;
  for (int i = 1; i < argc; i++) {
    args.push_back(argv[i]);
  }

  // Start engine
  Engine* engine = new Engine(Vector<int>(1600, 900), "Drone Simulation", args,
                              new MainAction());
  delete engine;

  return 0;
}
