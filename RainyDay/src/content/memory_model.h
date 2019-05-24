#ifndef MEMORY_MODEL_H
#define MEMORY_MODEL_H

#include "game.h"
#include <string>
#include <vector>
#include <array>

enum MemoryGameEventFlags{GE_INVALID, GE_ISFIRSTMOVE, GE_ISCORRECTMATCH};

struct MemoryCard{
	std::string text;
	std::string path_img;
	std::string path_audio;
	std::vector<MemoryCard*> linkedCards;
	int idx;
};

struct MemoryEvent{
	int team;
	int idx_selected;
};

struct MemoryStats: GameStats{
	std::vector<int> currentlySelectedCardsByTeam;
	std::array<std::array<int, 24>, 2> idxsFoundByTeam;
	std::vector<int> idxsFound;
	int currentTeam;
	MemoryGameEventFlags flag;
};

class MemoryModel{
	public:
		void readAllCardsFromFile(std::string path);
		void initGameCards(int num_cards);
		void initGameStats();
		bool validGameEvent(MemoryEvent e);
		bool isFirstMoveForTeam(MemoryEvent e);
		bool correctMatch(MemoryEvent e);
		void cleanupCurrentSelections(MemoryEvent e);
		void saveScore(MemoryEvent e);
		void moveToNextTeam(MemoryEvent e);
		void saveSelection(MemoryEvent e);
		void printContent();
		MemoryGameEventFlags getGameStatusFlag();
		bool testing;


	private:
		std::vector<MemoryCard*> _all_cards;
		std::vector<MemoryCard*> _game_cards;
		MemoryStats _gamestats;
		void _printArrayOfCards(std::vector<MemoryCard*> cards);
		MemoryCard* _firstCardSelected(MemoryEvent e){
			int idx_first_selected = _gamestats.currentlySelectedCardsByTeam[e.team];
			return _game_cards[idx_first_selected];
		}
		MemoryCard* _makeCard(std::string s);
		void _clearGameCards();
		void _buildGameCardsWithRequiredNumberOfPairs(int num_cards);
		void _logEvent(MemoryEvent e);
};


#endif // MEMORY_MODEL_H
