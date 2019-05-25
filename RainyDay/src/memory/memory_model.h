#ifndef MEMORY_MODEL_H
#define MEMORY_MODEL_H

#include "game.h"
#include "memory_info.h"
#include <string>
#include <vector>
#include <array>

class MemoryModel{
	public:
		void readAllCardsFromFile(std::string path);
		void initGameInfo(int num_cards);
		bool gameIsOver();
		bool validGameEvent(int idxSelected);
		bool isFirstMoveForTeam(int idxSelected);
		bool correctMatch(int idxSelected);
		void cleanupCurrentSelections(int idxSelected);
		void saveScore(int idxSelected);
		void moveToNextTeam(int idxSelected);
		void saveSelection(int idxSelected);
		void printContent();
		MemoryGameEventFlags getGameStatusFlag();
		MemoryInfo* getGameInfo(){return &_ginfo;}
		bool testing;


	private:
		std::vector<MemoryCard*> _all_cards;
		MemoryInfo _ginfo;
		void _printArrayOfCards(std::vector<MemoryCard*> cards);
		MemoryCard* _firstCardSelected(int idxSelected){
			int idx_first_selected = _ginfo.currentlySelectedCardsByTeam[_ginfo.currentTeam];
			return _ginfo.cards[idx_first_selected];
		}
		MemoryCard* _makeCard(std::string s);
		void _clearGameCards();
		void _initGameCards(int num_cards);
		void _assignCardsTheirGameIdx();
		void _incrementCardViewCount(int idxSelected);
		void _buildGameCardsWithRequiredNumberOfPairs(int num_cards);
		void _logEvent(int idxSelected);
};


#endif // MEMORY_MODEL_H
