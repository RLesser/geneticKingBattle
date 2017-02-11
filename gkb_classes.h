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
int MAX_MUTATION_SWAP = 10;
int PROPAGATION_LIST[] = {0,0,0,0,0,0,1,1,2,6};

typedef uniform_int_distribution<std::mt19937::result_type> DISTR;

DISTR castleDist(0,CASTLE_NUM-1);

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
	}
	

public:

	World(mt19937 &rng) {
		year = 0;
		for (int i = 0; i < KING_NUM; i++) {
			kingList.push_back(King(rng));
		}
	}

	void advanceYear() {
		year++;
		roundRobinBattle();
		//sort(kingList.begin(), kingList.end(), BattleComp_Less());

	}

	void printWorld() {
		cout << "Year: " << year << endl;
		for (int i = 0; i < KING_NUM; i++) {
			cout << i << ": ";
			kingList[i].printTroops();
		}
		cout << endl;
	}
	
};

#endif