/*	Jeren Raquel
 *	==Project Name==
 *	Description
 */
//* Custom
// Engine
#include "engine/headers/engine.hpp"
// Simulation
#include "simulation/headers/drone.hpp"

int main(int argc, char** argv) {
  Vector<int> size(900, 640);

  Engine* engine = new Engine(size, "Hello World");

  Drone* drone =
      new Drone(Vector<float>(450.0f, 320.0f), Vector<float>(10.0f, 10.0f),
                Vector3<float>(1.0f, 0.0f, 0.0f));
  engine->GetRenderer()->AddMesh(drone->GetMesh());

  engine->Start();
  delete drone;
  delete engine;

  return 0;
}
