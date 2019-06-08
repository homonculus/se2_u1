#ifndef TeamController_H
#define TeamController_H

#include "grid_controller.h"
#include "game.h"
#include "kinect_timer_window.h"
#include <vector>


enum TeamControllerEventFlag{TC_COLUMNSELECTED, TC_ROWSELECTED, TC_CELLSELECTED};

struct TeamControllerEventInfo{
	TeamControllerEventFlag type;
	int selected;
	int team;
};

class TeamControllerDelegate{
	public:
		virtual void teamControllerDidChange(TeamControllerEventInfo e) = 0;
};


class TeamController{
	public:
		TeamController(GridInfo* dimensions);
		TeamControllerDelegate* delegate;
		void start();
		void KinectTimerWindowControllerDidChange(int e);
		
	private:
		GridInfo* _dimensions;
};

# endif// TeamController_H