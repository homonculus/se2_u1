#ifndef MEMORYINFO_H
#define MEMORYINFO_H

#include <vector>
#include <string>
#include "game.h"

enum MemoryGameEventFlags{GE_INVALID, GE_ISFIRSTMOVE, GE_ISCORRECTMATCH};
enum MemoryCardStatus{CS_NOMATCH, CS_MATCH_TEAM0, CS_MATCH_TEAM1};

struct MemoryCard{
	std::string text;
	std::string path_img;
	std::string path_audio;
	std::vector<MemoryCard*> linkedCards;
	int idx;
	int status;
	int viewCount;
};

struct MemoryInfo: GameInfo{
	std::vector<int> currentlySelectedCardsByTeam;
	std::vector<std::vector<int> > idxsFoundByTeam;
	std::vector<int> idxsFound;
	int currentTeam;
	MemoryGameEventFlags flag;
	std::vector<MemoryCard*> cards;
};

#endif // MEMORYINFO_H