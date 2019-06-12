#ifndef MEMORYCONTROLLER_H
#define MEMORYCONTROLLER_H

#include "memory_model.h"
#include "memory_view.h"
#include "team_controller.h"
#include <string>
#include <vector>
#include "kinect_timer_window.h"
#include "memory_param_window.h"

class MemoryController: public TeamControllerDelegate, public KinectTimerWindowDelegate{
	public:
		std::string path_content;
		bool testing;
		void setContentPath(std::string path);
		void setDimensions(GridInfo* dims);
		void teamControllerDidChange(TeamControllerEventInfo e);
		void cardSelected(int idx);
		void setupGame();
		void startGame();
		void endGame();
		bool gameIsOver();
		void showWindow();
		void KinectTimerWindowControllerDidChange(int e);
		void KinectTimerWindowTimerFired();
		KinectTimerWindow* getWindow(){ return _gameWindow; };
		MemoryGameEventFlags getGameStatusFlag(){return _model->getGameStatusFlag();};
		MemoryInfo* getGameInfo(){return _model->getGameInfo();};

	private:
		GridInfo* _dimensions;
		MemoryModel* _model;
		MemoryView* _view;
		TeamController* _input;
		std::vector<int> _keyboardInput;
		MemoryParamWindow* _paramWindow;
		KinectTimerWindow* _gameWindow;
		KinectController* _kinectController;
		void _setupModel();
		void _setupView();
		void _setupInput();
		void _setupParamWindow();
		void _setupGameWindow();
		void _keyboardInputOccurred(int e);
};

#endif // MEMORYCONTROLLER_H
