#include <iostream>
#include <cassert>
#include "gkb_classes.h"

void king_tests() {
	King arthur(rng);

	cout << "testing troop sum: ";
	int sum = 0;
	for (int i = 0; i < TROOP_NUM; i++) {
		sum += arthur.getCastleTroops(i);
	}
	assert(sum == 100);
	cout << "PASSED!" << endl;
}


int main() {
	std::mt19937 rng;
    rng.seed(std::random_device()());

	cout << "Genetic King Battle - test suite" << endl << endl;

	cout << "Testing king construction..." << endl;
	
	


	return 0;
}