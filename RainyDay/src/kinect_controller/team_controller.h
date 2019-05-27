#ifndef TEAMCONTROLLER_H
#define TEAMCONTROLLER_H

#include "game.h"
#include "kinect_controller.h"

enum TeamControllerEventFlag{TC_COLUMNSELECTED, TC_ROWSELECTED, TC_CELLSELECTED};

struct TeamControllerEventInfo{
	TeamControllerEventFlag type;
	int selected;
};

class TeamController: public KinectControllerDelegate{
public:
	TeamController(GridInfo* dims);
	bool start();
	bool end();
	GridInfo* dimensions;
	int kinectController_imageReceived();


private:
	GridInfo* _dimensions;
	KinectController* _kinectController;
    bool protonect_paused;
};

#endif // TEAMCONTROLLER
