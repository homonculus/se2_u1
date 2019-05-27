#include "team_controller.h"
#include <iostream>

TeamController::TeamController(GridInfo* dims){
	_dimensions = dims;
	_kinectController = new KinectController();
	_kinectController->delegate = this;
}

bool TeamController::start(){
	_kinectController->startDevice();
	return true;
}

bool TeamController::end(){

	return true;
}

int TeamController::kinectControllerReceivedImage(){
	std::cout << "kinectControllerReceivedImage\n";
	TeamControllerEventInfo e = {TC_CELLSELECTED,5};
	delegate->teamControllerDidChange(e);
	return 0;
}