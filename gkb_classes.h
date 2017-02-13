#ifndef GKB_CLASSES_H
#define GKB_CLASSES_H

#include <random> // for mt19937, uniform_int_distribution
#include <chrono> // for high_resolution_clock
#include <iostream>
#include "Tournament.h"

using namespace std;

int KING_NUM = 10; // K in complexity analysis
int	CASTLE_NUM = 10; // C in complexity analysis
int TROOP_NUM = 100; // T in complexity analysis
int YEAR_NUM = 1000; // Y in complexity analysis
int MAX_MUTATION_SWAP = 10; //max num to be swapped in mutation
int PROPAGATION_LIST[] = {0,0,1,1,1,1,1,1,2,2}; //children for each king

typedef uniform_int_distribution<std::mt19937::result_type> DISTR;

//Distribution of castles
DISTR castleDist(0,CASTLE_NUM-1);
//Distribution of mutations
DISTR mutationSizeDist(1,MAX_MUTATION_SWAP);


class King {
private:
	vector<int> troopPlacement;
	int score;

public:
	King(mt19937 &rng)
		: troopPlacement(CASTLE_NUM, 0), score(0) {
		for (int i = 0; i < TROOP_NUM; ++i) {
			troopPlacement[castleDist(rng)]++;
		}
	}

	King(vector<int> troops_in) 
		: troopPlacement(troops_in), score(0) {}

	//castlenum must be at least 1
	void printTroops() {
		cout << "S:" << score << " ";
		cout << "[" << troopPlacement[0];
		for (int i = 1; i < CASTLE_NUM; i++) {
			cout << "," << troopPlacement[i];
		}
		cout << "]" << endl;
	}

	size_t getCastleTroops(size_t idx) {
		if (idx >= CASTLE_NUM) {
			cerr << "castle index too large" << endl;
			exit(1);
		}
		return  troopPlacement[idx];
	}

	// generates a child of the current king
	// A child is different than it's parent based on the following process:
	// A number of troops between 1 and MAX_MUTATION_SWAP is moved from one
	// castle to another castle.
	// If the castle losing troops would be < 0 or the castle gaining troops
	// would be > 0, then the max viable swap is executed.
	vector<int> generateChild(mt19937 &rng) {
		int mutationSize = mutationSizeDist(rng);
		int donorCastle = castleDist(rng);
		int recipCastle = castleDist(rng);
		// if the mutation would be larger than the donor castle's size...
		if (mutationSize > troopPlacement[donorCastle]) {
			//set mutation size to the max troops that can be taken
			mutationSize = troopPlacement[donorCastle];
		}
		// also, if the mutation would be larger than the recipiant castle's
		// remaining spots, (and remaining spots < previous constraint)...
		if (mutationSize > (TROOP_NUM - troopPlacement[recipCastle])) {
			mutationSize = (TROOP_NUM - troopPlacement[recipCastle]);
		}

		vector<int> childVec(troopPlacement.begin(), troopPlacement.end());
		childVec[donorCastle] -= mutationSize;
		childVec[recipCastle] += mutationSize;

		return childVec;
	}

	bool operator<(const King &rhs) const {
		return score < rhs.score;
	}

	void victory() {
		score++;
	}

	int getScore() {
		return score;
	}

	//~King();
};













class World {
private:
	//TODO: probably better to use pointer to king, but this works for now 
	vector<King> kingList;
	int year;
	mt19937 &rng;


	size_t kingBattle(size_t kingAIdx, size_t kingBIdx) {
		int pointsA = 0;
		int pointsB = 0;
		for (int i = 0; i < CASTLE_NUM; i++) {
			//cout << A.getCastleTroops(i) << " " << B.getCastleTroops(i) << endl;
			if (kingList[kingAIdx].getCastleTroops(i) > 
				kingList[kingBIdx].getCastleTroops(i)) {
				//cout << "A wins castle " << i << endl;
				pointsA += (i+1);
			} else if (kingList[kingAIdx].getCastleTroops(i) < 
					   kingList[kingBIdx].getCastleTroops(i)) {
				//cout << "B wins castle " << i << endl;
				pointsB += (i+1);
			}
		}
		if (pointsA > pointsB) {
			return kingAIdx;
		} else if (pointsA < pointsB) {
			return kingBIdx;
		} else { 
			//king_num if no winner this round
			//be sure to account for this!!!
			return KING_NUM;
		}
	}

	void roundRobinBattle() {
		for (int i = 0; i < KING_NUM; i++) {
			if (kingList[i].getScore() != 0) {
				cerr << "King about to battle has nonzero score" << endl;
				exit(1);
			}
		}
		RoundRobin RR(KING_NUM);
		pair<size_t, size_t> currentMatch;
		while (RR.getMatch(currentMatch)) {
			size_t winnerIdx = kingBattle(currentMatch.first, currentMatch.second);
			kingList[winnerIdx].victory();
		}
		sort(kingList.begin(), kingList.end());
	}

	void nextGeneration() {
		vector<King> newGen;
		for (int i = 0; i < KING_NUM; i++) {
			for (int j = 0; j < PROPAGATION_LIST[i]; j++) {
				newGen.push_back(King(kingList[i].generateChild(rng)));
			}
		}
		kingList = newGen;
	}
	

public:

	World(mt19937 &rng_in) : rng(rng_in) {
		year = 0;
		for (int i = 0; i < KING_NUM; i++) {
			kingList.push_back(King(rng));
		}
	}

	void advanceYear() {
		year++;
		roundRobinBattle();
		nextGeneration();
		//sort(kingList.begin(), kingList.end(), BattleComp_Less());
	}

	void printWorld(bool avg) {
		if (!avg) {
			cout << "Year: " << year << endl;
			for (int i = 0; i < KING_NUM; i++) {
				cout << i << ": ";
				kingList[i].printTroops();
			}
		} else {
			vector<double> avgs = getWorldAverage();
			cout << year << ",";
			for (int i = 0; i < CASTLE_NUM; i++) {
				cout << avgs[i];
				if (i != CASTLE_NUM-1) {
					cout << ",";
				}
			}
		}
		cout << endl;
	}

	vector<double> getWorldAverage() {
		vector<int> sums(CASTLE_NUM, 0);
		vector<double> avgs(CASTLE_NUM, 0);
		//cout << "TESTeee" << endl;
		for (int i = 0; i < CASTLE_NUM; i++) {
			//cout << i << endl;
			for(int j = 0; j < KING_NUM; j++) {
				sums[i] += kingList[j].getCastleTroops(i);
			}
			avgs[i] = sums[i] / (double)KING_NUM;
		}
		return avgs;
	}
	
};

#endif