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
		bool validGameEvent(MemoryEvent e);
		bool isFirstMoveForTeam(MemoryEvent e);
		bool correctMatch(MemoryEvent e);
		void cleanupCurrentSelections(MemoryEvent e);
		void saveScore(MemoryEvent e);
		void moveToNextTeam(MemoryEvent e);
		void saveSelection(MemoryEvent e);
		void printContent();
		MemoryGameEventFlags getGameStatusFlag();
		MemoryInfo* getGameInfo(){return &_ginfo;}
		bool testing;


	private:
		std::vector<MemoryCard*> _all_cards;
		MemoryInfo _ginfo;
		void _printArrayOfCards(std::vector<MemoryCard*> cards);
		MemoryCard* _firstCardSelected(MemoryEvent e){
			int idx_first_selected = _ginfo.currentlySelectedCardsByTeam[e.team];
			return _ginfo.cards[idx_first_selected];
		}
		MemoryCard* _makeCard(std::string s);
		void _clearGameCards();
		void _initGameCards(int num_cards);
		void _assignCardsTheirGameIdx();
		void _incrementCardViewCount(MemoryEvent e);
		void _buildGameCardsWithRequiredNumberOfPairs(int num_cards);
		void _logEvent(MemoryEvent e);
};


#endif // MEMORY_MODEL_H
