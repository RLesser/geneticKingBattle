#include <iostream>
#include "gkb_classes.h"

using namespace std;

int main() {
	std::mt19937 rng;
    rng.seed(std::random_device()());

    World world(rng);

    world.printWorld();
    world.advanceYear();
    world.printWorld();

	// cout << r.randNum() << endl;
	// cout << r.randNum() << endl;
}