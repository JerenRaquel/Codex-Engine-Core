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
#include "simulation/headers/alpha.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <drone count>" << std::endl;
    return 1;
  }

  Vector<int> size(1600, 900);
  Vector<float> scale(2.5f, 2.5f);
  unsigned int droneCount = std::atoi(argv[1]);

  Engine* engine = new Engine(size, "Drone Simulation");
  engine->CompileComputeShader("CalulateDistances.comp", "CalulateDistances");

  for (unsigned int i = 0; i < droneCount; i++) {
    Vector<float>* position =
        new Vector<float>(std::rand() % engine->GetWindowSize().x,
                          std::rand() % engine->GetWindowSize().y);
    engine->AddDrone(new Boids(position, scale), "Boids");
  }

  for (unsigned int i = 0; i < 10; i++) {
    // for (unsigned int i = 0; i < droneCount; i++) {
    Vector<float>* position =
        new Vector<float>(std::rand() % engine->GetWindowSize().x,
                          std::rand() % engine->GetWindowSize().y);
    // engine->AddDrone(new Alpha(position, Vector<float>(2.5f, 2.5f)),
    // "Alpha");
    engine->AddDrone(new Alpha(position, Vector<float>(10.0f, 10.0f)), "Alpha");
  }

  engine->Start();
  delete engine;

  return 0;
}
