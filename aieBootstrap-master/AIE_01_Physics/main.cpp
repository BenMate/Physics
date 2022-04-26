#include "AIE_01_PhysicsApp.h"

int main() {
	
	// allocation
	auto app = new AIE_01_PhysicsApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}