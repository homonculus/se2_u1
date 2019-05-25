#ifndef GAME_H
#define GAME_H

#include <vector>

struct GameEvent{

};

struct GridInfo{
	int n_rows;
	int n_cols;
	int n;
};

struct GameInfo{
	std::vector<int> teamScores;
	int currentTeam;
};



#endif // GAME_H