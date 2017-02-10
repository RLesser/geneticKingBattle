#include <iostream>
#include "gkb_classes.h"

using namespace std;

int main() {
	std::mt19937 rng;
    rng.seed(std::random_device()());

    cout << castleDist(rng) << endl;
    King a(rng);
    King b(rng);
    a.printTroops();


	// cout << r.randNum() << endl;
	// cout << r.randNum() << endl;
}