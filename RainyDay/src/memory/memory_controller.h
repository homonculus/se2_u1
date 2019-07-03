#ifndef MEMORYCONTROLLER_H
#define MEMORYCONTROLLER_H

#include "memory_model.h"
#include "memory_view.h"
// #include "team_controller.h"
#include <string>
#include <vector>
#include "memory_game_window.h"
#include "memory_param_window.h"

class MemoryController: public MemoryParamWindowDelegate{
	public:
		std::string path_content;
		bool testing;
		void setContentPath(std::string path);
		void setDimensions(GridInfo* dims);
		// void teamControllerDidChange(TeamControllerEventInfo e);
		void cardSelected(int idx);
		void setupGame();
		void startGame();
		void endGame();
		bool gameIsOver();
		void showWindow();
		MemoryGameWindow* getGameWindow(){ return _gameWindow; };
		MemoryParamWindow* getParamWindow(){ return _paramWindow; };
		MemoryGameEventFlags getGameStatusFlag(){return _model->getGameStatusFlag();};
		MemoryInfo* getGameInfo(){return _model->getGameInfo();};
        void MemoryParamWindow_inputChanged(std::vector<int> idxActivityBySide);
		void MemoryParamWindow_startGame(int nrows, int ncols);
		void MemoryParamWindow_endGame(int e);

	private:
		GridInfo* _dimensions;
		MemoryModel* _model;
		MemoryView* _view;
		// TeamController* _input;
		// std::vector<int> _keyboardInput;
		MemoryParamWindow* _paramWindow;
		MemoryGameWindow* _gameWindow;
		void _setupModel();
		void _setupView();
		void _setupInput();
		void _setupParamWindow();
		void _setupGameWindow();
		// void _keyboardInputOccurred(int e);
		bool _gameStarted;
};

#endif // MEMORYCONTROLLER_H
