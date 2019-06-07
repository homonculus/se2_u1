#ifndef MEMORYCONTROLLER_H
#define MEMORYCONTROLLER_H

#include "memory_model.h"
#include "memory_view.h"
#include "team_controller.h"
#include <string>
#include <vector>
#include "kinect_timer_window.h"

class MemoryController: public TeamControllerDelegate{
	public:
		std::string path_content;
		void setContentPath(std::string path);
		void setDimensions(GridInfo* dims);
		void teamControllerDidChange(TeamControllerEventInfo e);
		void cardSelected(int idx);
		void setupGame();
		void startGame();
		void endGame();
		bool gameIsOver();
		MemoryGameEventFlags getGameStatusFlag(){return _model->getGameStatusFlag();};
		MemoryInfo* getGameInfo(){return _model->getGameInfo();};
		bool testing;
		void showWindow();
		KinectTimerWindow* getWindow(){ return _window; };

	private:
		std::vector<MemoryCard*> _all_cards;
		std::vector<MemoryCard*> _game_cards;
		GridInfo* _dimensions;
		MemoryModel* _model;
		MemoryView* _view;
		TeamController* _input;
		std::vector<int> _keyboardInput;
		KinectTimerWindow* _window;
};


#endif // MEMORYCONTROLLER_H
