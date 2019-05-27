#include "memory_controller.h"
#include "team_controller.h"
#include <iostream>

void MemoryController::setContentPath(std::string path){
	path_content = path;
}

void MemoryController::setDimensions(GridInfo* dims){
	_dimensions = dims;
}

void MemoryController::setupGame(){
	_model = new MemoryModel();
	_model->testing = testing;
	_model->readAllCardsFromFile(path_content);
	_model->initGameInfo(_dimensions->n);

	_view = new MemoryView();
	_view->initGameView(_model->getGameInfo(), _dimensions);
}

void MemoryController::teamControllerDidChange(TeamControllerEventInfo e){
	std::cout << "MemoryController::teamControllerDidChange : type(" << e.type << ") selected(" << e.selected << ")\n";
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