#ifndef GKB_CLASSES_H
#define GKB_CLASSES_H

#include <random> // for mt19937, uniform_int_distribution
#include <chrono> // for high_resolution_clock
#include <iostream>

using namespace std;

int	CASTLE_NUM = 10;
int TROOP_NUM = 100;
int MAX_MUTATION_SWAP = 10;
int PROPAGATION_LIST[] = {6,2,1,1,0,0,0,0,0,0};

typedef uniform_int_distribution<std::mt19937::result_type> DISTR;

DISTR castleDist(0,CASTLE_NUM-1);

class King {
private:
	vector<int> troopPlacement;

public:
	King(mt19937 rng)
		: troopPlacement(CASTLE_NUM, 0) {
		for (int i = 0; i < TROOP_NUM; ++i) {
			troopPlacement[castleDist(rng)]++;
		}
	}

	//castlenum must be at least 1
	void printTroops() {
		cout << "[" << troopPlacement[0];
		for (int i = 1; i < CASTLE_NUM; i++) {
			cout << "," << troopPlacement[i];
		}
		cout << "]" << endl;
	}

	//~King();
};

class World {
private:
	vector<King> kingList;

public:
	
};

#endif