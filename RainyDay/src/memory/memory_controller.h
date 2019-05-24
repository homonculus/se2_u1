#ifndef MEMORYCONTROLLER_H
#define MEMORYCONTROLLER_H

#include "memory_model.h"
#include <string>
#include <vector>

class MemoryController{
	public:
		std::string path_content;
		void setContentPath(std::string path);
		void gameEvent(MemoryEvent e);
		void setupGame();
		void startGame();
		void endGame();
		void setDimensions(int n_rows, int n_cols);
		GridInfo getDimensions();
		MemoryGameEventFlags getGameStatusFlag(){return _model->getGameStatusFlag();};
		bool testing;

	private:
		std::vector<MemoryCard*> _all_cards;
		std::vector<MemoryCard*> _game_cards;
		GridInfo _dimensions;
		MemoryModel* _model;
};


#endif // MEMORYCONTROLLER_H
