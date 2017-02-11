#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <deque>

using namespace std;


class RoundRobin {
private:
	deque<size_t> teamIdxUpper;
	deque<size_t> teamIdxLower;
	int roundNum;
	int matchInRound;

	void nextRound() {
		matchInRound = 0;
		roundNum++;
		size_t tempFirst;
		//1. Pop 1 from front of upper
		tempFirst = teamIdxUpper.front();
		teamIdxUpper.pop_front();
		//2. Push front of lower to front of upper
		teamIdxUpper.push_front(teamIdxLower.front());
		teamIdxLower.pop_front();
		//3. Push 1 back onto front of upper
		teamIdxUpper.push_front(tempFirst);
		//4. Push back of upper onto back of lower
		teamIdxLower.push_back(teamIdxUpper.back());
		teamIdxUpper.pop_back();
	}


public:
	RoundRobin(vector<size_t> inputVec) {
		//TODO: make this work for odd num teams with bye
		if (inputVec.size() == 0 || inputVec.size()%2 == 1) {
			cerr << "Invalid tournament size" << endl;
			exit(1);
		}
		roundNum = 0;
		matchInRound = 0;
		for (int i = 0; i < inputVec.size()/2; i++) {
			teamIdxUpper.push_back(inputVec[i]);
		}
		for (int j = inputVec.size()/2+1; j < inputVec.size(); j++) {
			teamIdxLower.push_front(inputVec[j]);
		}
	}

	RoundRobin(int teamCount) {
		//TODO: make this work for odd num teams with bye
		if (teamCount < 1 || teamCount%2 == 1) {
			cerr << "Invalid tournament size" << endl;
			exit(1);
		}
		roundNum = 0;
		matchInRound = 0;
		for (int i = 0; i < teamCount/2; i++) {
			teamIdxUpper.push_back(i);
		}
		for (int j = teamCount/2; j < teamCount; j++) {
			teamIdxLower.push_front(j);
		}
	}

	//sets match to right pair
	//return bool is true until the RR ends
	bool getMatch(pair<size_t,size_t> &match) {
		//get pair first, then fix deques for next match
		match.first = teamIdxUpper[matchInRound];
		match.second = teamIdxLower[matchInRound];
		matchInRound++;
		if (roundNum == teamIdxUpper.size()+teamIdxLower.size()-1) {
			return false;
		}
		if (matchInRound == teamIdxUpper.size()) {
			nextRound();
		}
		return true;

	}



};

#endif