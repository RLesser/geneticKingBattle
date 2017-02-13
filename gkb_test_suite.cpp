#include <iostream>
#include <cassert>
#include "gkb_classes.h"

void king_tests(mt19937 &rng) {

	cout << "Testing king..." << endl;

	King arthur(rng);

	cout << "testing troop sum: ";
	int sum = 0;
	for (int i = 0; i < CASTLE_NUM; i++) {
		sum += arthur.getCastleTroops(i);
	}
	assert(sum == 100);
	cout << "PASSED!" << endl;

	cout << "All testing for king PASSED." << endl;
}

void world_tests(mt19937 &rng) {

	cout << "Testing world..." << endl;

	World mars(rng);

	cout << "testing king amount: ";


}

int main() {
	std::mt19937 rng;
    rng.seed(std::random_device()());

	cout << "Genetic King Battle - test suite" << endl << endl;

	king_tests(rng);

	cout << endl;

	
	


	return 0;
}