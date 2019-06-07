#include "memory_controller.h"
#include <iostream>

void MemoryController::setContentPath(std::string path){
	path_content = path;
}

void MemoryController::setDimensions(GridInfo* dims){
	_dimensions = dims;
}

void MemoryController::setupGame(){
	// setup model
	_model = new MemoryModel();
	_model->testing = true;
	_model->readAllCardsFromFile(path_content);
	_model->initGameInfo(_dimensions->n);

	// setup view
	_view = new MemoryView();
	_view->initGameView(_model->getGameInfo(), _dimensions);
	_view->refreshCellSelections();

	// setup team controller (will conversion kinect -> team moves)
	_input = new TeamController(_dimensions);
	_input->delegate = this;
	
	// setup window
	_window = new KinectTimerWindow();
	_window->delegate = _input;
	_window->setRenderArea(_view->getGrid());
	_window->setTitle("hello");
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
	_window->show();
}
