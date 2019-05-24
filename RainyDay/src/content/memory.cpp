
#include "memory.h"
#include "memory_model.h"
#include <iostream>

void Memory::setContentPath(std::string path){
	path_content = path;
}

void Memory::setupGame(){
	_model = new MemoryModel();
	_model->testing = testing;
	_model->readAllCardsFromFile(path_content);
	_model->initGameCards(_dimensions.n);
	_model->initGameStats();
}

GridInfo Memory::getDimensions(){
	return _dimensions;
}

void Memory::setDimensions(int n_rows, int n_cols){
	_dimensions.n_rows = n_rows;
	_dimensions.n_cols = n_cols;
	_dimensions.n = n_rows * n_cols;
}

void Memory::gameEvent(MemoryEvent e){
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
}