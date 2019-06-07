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
	// int v = e-49;
	// if (v >-1 && v < 10){
	// 	if (_keyboardInput.size() == 0){
	// 		if (v < _dimensions->n_cols){
	// 			TeamControllerEventInfo event = {TC_COLUMNSELECTED, v, 0};
	// 			teamControllerDidChange(event);
	// 			_keyboardInput.push_back(v);
	// 		}
	// 	}
	// 	else if (_keyboardInput.size() == 1){
	// 		if (v < _dimensions->n_rows){
	// 			TeamControllerEventInfo event = {TC_ROWSELECTED, v, 0};
	// 			teamControllerDidChange(event);
	// 			_keyboardInput.push_back(v);
	// 		}
	// 	}
	// 	else if (_keyboardInput.size() == 2){
	// 		_keyboardInput.clear();
	// 		_view->setSelectedRow(-1);
	// 		_view->setSelectedColumn(-1);
	// 		_view->refreshCellSelections();
	// 		// int command = _keyboardInput[1]*_dimensions->n_cols + _keyboardInput[0];
	// 	}
	// }

	std::cout << "TeamController::KinectTimerWindowControllerDidChange : " << e << "\n";
}