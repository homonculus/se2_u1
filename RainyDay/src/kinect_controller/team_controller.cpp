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

int TeamController::kinectController_imageReceived(){
	std::cout << "kinectController_imageReceived\n";
	return 0;
}