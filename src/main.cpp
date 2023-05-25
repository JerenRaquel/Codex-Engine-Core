/*	Jeren Raquel
 *	==Drone Simulation==
 *	Description
 */
// Std
#include <cstdlib>
#include <vector>
// Custom
#include "engine/headers/engine.hpp"
// Simulation
#include "simulation/headers/boids.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <drone count>" << std::endl;
    return 1;
  }

  Vector<int> size(1600, 900);
  Vector<float> scale(2.5f, 2.5f);
  unsigned int droneCount = std::atoi(argv[1]);

  Engine* engine = new Engine(size, "Drone Simulation");

  for (unsigned int i = 0; i < droneCount; i++) {
    Vector<float> position(std::rand() % engine->GetWindowSize().x,
                           std::rand() % engine->GetWindowSize().y);
    engine->AddDrone(new Boids(position, scale));
  }

  engine->Start();
  delete engine;

  return 0;
}
