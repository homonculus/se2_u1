#include "team_controller.h"
#include <iostream>

TeamController::TeamController(GridInfo* dimensions){
	_dimensions = dimensions;
	
}

// void TeamController::gridControllerDidChange(std::vector<int> cells){
// 	std::cout << "TeamController::gridControllerDidChange\n";
// 	TeamControllerEventInfo e = {TC_CELLSELECTED, 0};
// 	delegate->teamControllerDidChange(e);
// }

void TeamController::start(){
}

void TeamController::MemoryParamWindowDidChange(int e){
	std::cout << "TeamController::MemoryParamWindowDidChange : " << e << "\n";
}