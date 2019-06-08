#include "grid_controller.h"
#include <iostream>

GridController::GridController(int _n_rows, int _n_cols){
	n_rows = _n_rows;
	n_cols = _n_cols;
	_grid.reserve(_n_rows*_n_cols);
	_kinectController = new KinectController();

	for (int r=0;r<_n_rows;r++){
		for (int c=0;c<_n_cols;c++){
			_grid.push_back(GC_INACTIVE);
		}
	}
}

bool GridController::start(){
	_kinectController->startDevice();
	return true;
}

bool GridController::end(){
	return true;
}

int GridController::_thresholdForCell(cv::Mat depthImage, int idx_start_row, int idx_end_row, int idx_start_col, int idx_end_col){
	// for (int r=idx_start_row;r<idx_end_row;r++){
	// 	for (int c=idx_start_col;c<idx_end_col;c++){
	// 		// depthImage.at(r,c);
	// 	}
	// }
	return 0;
}

// std::vector<int> GridController::getActiveCells(){
// 	_kinectController->getDepthImage();
// 	return _grid;
// }



