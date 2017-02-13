#include <iostream>
#include "gkb_classes.h"

using namespace std;

int main() {
	std::mt19937 rng;
    rng.seed(std::random_device()());

    World world(rng);

    //world.printWorld();
    cout << "year";
	for (int i = 0; i < CASTLE_NUM; i++) {
		cout << "," << i;
	}
	cout << endl;
    for (int i = 0; i < YEAR_NUM; ++i) {
    	world.advanceYear();
    	world.printWorld(true);
    }

	// cout << r.randNum() << endl;
	// cout << r.randNum() << endl;
}