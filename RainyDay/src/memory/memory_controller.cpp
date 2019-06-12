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
	// _kinectController = new KinectController();
	// _kinectController->startDevice();
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
	_input = new TeamController(_dimensions);
	_input->delegate = this;
}

void MemoryController::_setupParamWindow(){
	// must be before setupInput
	_paramWindow = new MemoryParamWindow();
}

void MemoryController::_setupGameWindow(){
	// must be before setupInput
	_gameWindow = new KinectTimerWindow();
	_gameWindow->delegate = (KinectTimerWindowDelegate*)this; // timer events go directly to team controller
	_gameWindow->setRenderArea(_view->getGrid());
	_gameWindow->setTitle("Memory");
}

void MemoryController::startGame(){
	_input->start();
}

void MemoryController::teamControllerDidChange(TeamControllerEventInfo e){
	std::cout << "MemoryController::teamControllerDidChange : type(" << e.type << ") selected(" << e.selected << ")\n";
	if (e.type == TC_CELLSELECTED){
		cardSelected(e.selected);
	}
	else if (e.type == TC_ROWSELECTED){
		_view->setSelectedRow(e.selected);
		_view->refreshCellSelections();
	}
	else if (e.type == TC_COLUMNSELECTED){
		_view->setSelectedColumn(e.selected);
		_view->refreshCellSelections();
	}
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


void MemoryController::KinectTimerWindowControllerDidChange(int e){
	std::cout << "MemoryController::KinectTimerWindowControllerDidChange : " << e << "\n";
}

void MemoryController::KinectTimerWindowTimerFired(){


	// std::cout << "MemoryController::KinectTimerWindowTimerFired : \n";
	// KinectImage* image = _kinectController->getDepthImage();
	// std::cout << "MemoryController::KinectTimerWindowTimerFired : \n";

	// _paramWindow->setCallibrationImage(image->data, image->width, image->height);
}

void MemoryController::_keyboardInputOccurred(int e){
	// can be removed, don't want keyboard commands
	int v = e-49;
	if (v >-1 && v < 10){
		if (_keyboardInput.size() == 0){
			if (v < _dimensions->n_cols){
				TeamControllerEventInfo event = {TC_COLUMNSELECTED, v, 0};
				teamControllerDidChange(event);
				_keyboardInput.push_back(v);
			}
		}
		else if (_keyboardInput.size() == 1){
			if (v < _dimensions->n_rows){
				TeamControllerEventInfo event = {TC_ROWSELECTED, v, 0};
				teamControllerDidChange(event);
				_keyboardInput.push_back(v);
			}
		}
		else if (_keyboardInput.size() == 2){
			_keyboardInput.clear();
			_view->setSelectedRow(-1);
			_view->setSelectedColumn(-1);
			_view->refreshCellSelections();
			// int command = _keyboardInput[1]*_dimensions->n_cols + _keyboardInput[0];
		}
	}
}
