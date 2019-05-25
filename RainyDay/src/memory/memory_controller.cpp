#include "memory_controller.h"
#include <iostream>

void MemoryController::setContentPath(std::string path){
	path_content = path;
}

void MemoryController::setDimensions(int n_rows, int n_cols){
	_dimensions.n_rows = n_rows;
	_dimensions.n_cols = n_cols;
	_dimensions.n = n_rows * n_cols;
}

GridInfo MemoryController::getDimensions(){
	return _dimensions;
}

void MemoryController::setupGame(){
	_model = new MemoryModel();
	_model->testing = testing;
	_model->readAllCardsFromFile(path_content);
	_model->initGameInfo(_dimensions.n);

	_view = new MemoryView();
	_view->initGameView(_model->getGameInfo(), _dimensions);
}

void MemoryController::cardSelected(MemoryEvent e){
	if (_model->validGameEvent(e)){
		if (_model->isFirstMoveForTeam(e)){
			_model->saveSelection(e);
		}
		else{
			if (_model->correctMatch(e)){
				_model->saveScore(e);
			}
			else{
				_model->moveToNextTeam(e);
			}
			_model->cleanupCurrentSelections(e);
		}
	}
	_view->updateView();
}