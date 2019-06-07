#ifndef TeamController_H
#define TeamController_H

#include "grid_controller.h"
#include "game.h"
#include "kinect_timer_window.h"


enum TeamControllerEventFlag{TC_COLUMNSELECTED, TC_ROWSELECTED, TC_CELLSELECTED};

struct TeamControllerEventInfo{
	TeamControllerEventFlag type;
	int selected;
	int team;
};

class TeamControllerDelegate : public KinectTimerWindowDelegate{
public:
	virtual void teamControllerDidChange(TeamControllerEventInfo e) = 0;
};


class TeamController:GridControllerDelegate{
	public:
		TeamController(GridInfo* dimensions);
		TeamControllerDelegate* delegate;
		void gridControllerDidChange(std::vector<int> cells);
		void start();
		void KinectTimerWindowControllerDidChange(int e);
		
	private:
		GridInfo* _dimensions;
		GridController* _gridController;
};

# endif// TeamController_H