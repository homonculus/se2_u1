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

int TeamController::kinectControllerReceivedImage(cv::Mat depthImage){
	std::cout << "kinectControllerReceivedImage\n";
	TeamControllerEventInfo e = {TC_CELLSELECTED,5};
	

	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display Image",depthImage);

	delegate->teamControllerDidChange(e);
	return 0;
}