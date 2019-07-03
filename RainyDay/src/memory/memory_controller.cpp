#include "memory_controller.h"
#include <iostream>

void MemoryController::setContentPath(std::string path){
	path_content = path;
}

void MemoryController::setDimensions(GridInfo* dims){
	_dimensions = dims;
}

void MemoryController::setupGame(){
	_setupModel();
	_setupView();
	_setupInput();
	_setupParamWindow();
	_setupGameWindow();
	std::cout << "MemoryController::finished starting device\n";
}

void MemoryController::_setupModel(){
	_model = new MemoryModel();
	_model->testing = true;
	_model->readAllCardsFromFile(path_content);
	_model->initGameInfo(_dimensions->n);
}

void MemoryController::_setupView(){
	_view = new MemoryView();
	_view->initGameView(_model->getGameInfo(), _dimensions);
	_view->refreshCellSelections();
}

void MemoryController::_setupInput(){
}

void MemoryController::_setupParamWindow(){
	// must be before setupInput
	_paramWindow = new MemoryParamWindow();
	_paramWindow->delegate = this;
}

void MemoryController::_setupGameWindow(){
	// must be before setupInput
	_gameWindow = new MemoryGameWindow();
	_gameWindow->setRenderArea(_view->getGrid());
	_gameWindow->setTitle("Memory");
}

void MemoryController::startGame(){
	// _input->start();
}

// void MemoryController::teamControllerDidChange(TeamControllerEventInfo e){
// 	std::cout << "MemoryController::teamControllerDidChange : type(" << e.type << ") selected(" << e.selected << ")\n";
// 	if (e.type == TC_CELLSELECTED){
// 		cardSelected(e.selected);
// 	}
// 	else if (e.type == TC_ROWSELECTED){
// 		_view->setSelectedRow(e.selected);
// 		_view->refreshCellSelections();
// 	}
// 	else if (e.type == TC_COLUMNSELECTED){
// 		_view->setSelectedColumn(e.selected);
// 		_view->refreshCellSelections();
// 	}
// }

void MemoryController::MemoryParamWindow_inputChanged(std::vector<int> idxActivityBySide){
	int idx_h = 0;
	int idx_v = 2;

	std::cout << "MemoryController::MemoryParamWindow_inputChanged 1\n";
	if (idxActivityBySide[idx_h] > -1){ _view->setSelectedColumn(idxActivityBySide[idx_h]);}
	if (idxActivityBySide[idx_v] > -1){ _view->setSelectedRow(idxActivityBySide[idx_v]);}
	_view->refreshCellSelections();
	std::cout << "MemoryController::MemoryParamWindow_inputChanged 2 :" << idxActivityBySide[idx_h] << " " << idxActivityBySide[idx_v] << "\n";

}

void MemoryController::MemoryParamWindow_startGame(int nrows, int ncols){

}

void MemoryController::MemoryParamWindow_endGame(int e){

}

void MemoryController::cardSelected(int i){
	if (_model->validGameEvent(i)){
		if (_model->isFirstMoveForTeam(i)){
			_model->saveSelection(i);
		}
		else{
			if (_model->correctMatch(i)){
				_model->saveScore(i);
			}
			else{
				_model->moveToNextTeam(i);
			}
			_model->cleanupCurrentSelections(i);
		}
	}
	_view->updateView();
}

bool MemoryController::gameIsOver(){
	return _model->gameIsOver();
}

void MemoryController::showWindow(){
	_paramWindow->show();
	_gameWindow->show();
}


// void MemoryController::_keyboardInputOccurred(int e){
// 	// can be removed, don't want keyboard commands
// 	int v = e-49;
// 	if (v >-1 && v < 10){
// 		if (_keyboardInput.size() == 0){
// 			if (v < _dimensions->n_cols){
// 				TeamControllerEventInfo event = {TC_COLUMNSELECTED, v, 0};
// 				teamControllerDidChange(event);
// 				_keyboardInput.push_back(v);
// 			}
// 		}
// 		else if (_keyboardInput.size() == 1){
// 			if (v < _dimensions->n_rows){
// 				TeamControllerEventInfo event = {TC_ROWSELECTED, v, 0};
// 				teamControllerDidChange(event);
// 				_keyboardInput.push_back(v);
// 			}
// 		}
// 		else if (_keyboardInput.size() == 2){
// 			_keyboardInput.clear();
// 			_view->setSelectedRow(-1);
// 			_view->setSelectedColumn(-1);
// 			_view->refreshCellSelections();
// 			// int command = _keyboardInput[1]*_dimensions->n_cols + _keyboardInput[0];
// 		}
// 	}
// }
