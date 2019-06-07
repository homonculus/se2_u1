#include "team_controller.h"
#include <iostream>

TeamController::TeamController(GridInfo* dimensions){
	_dimensions = dimensions;
	_gridController = new GridController(_dimensions->n_rows, _dimensions->n_cols);
	_gridController->delegate = this;
	
}


void TeamController::gridControllerDidChange(std::vector<int> cells){
	std::cout << "TeamController::gridControllerDidChange\n";
	TeamControllerEventInfo e = {TC_CELLSELECTED, 0};
	delegate->teamControllerDidChange(e);
}

void TeamController::start(){
	_gridController->start();
}

void TeamController::KinectTimerWindowControllerDidChange(int e){

	std::cout << "TeamController::KinectTimerWindowControllerDidChange : " << e << "\n";
}