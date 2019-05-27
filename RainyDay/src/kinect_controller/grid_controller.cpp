#include "grid_controller.h"
#include <iostream>

GridController::GridController(int _n_rows, int _n_cols){
	n_rows = _n_rows;
	n_cols = _n_cols;
	_grid.reserve(_n_rows*_n_cols);
	_kinectController = new KinectController();
	_kinectController->delegate = this;
}

bool GridController::start(){
	_kinectController->startDevice();
	return true;
}

bool GridController::end(){
	return true;
}

int GridController::kinectControllerReceivedImage(cv::Mat depthImage){
	std::cout << "GridController::kinectControllerReceivedImage\n";
	// cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
	// cv::imshow("Display Image",depthImage);
	// for (int r=0;r<depthImage.rows;r++){
	// 	for (int c=0;c<depthImage.cols;c++){
	// 		// depthImage.at(r,c);
	// 	}
	// }
	delegate->gridControllerDidChange(_grid);
	return 0;
}

int GridController::_thresholdForCell(cv::Mat depthImage, int idx_start_row, int idx_end_row, int idx_start_col, int idx_end_col){
	// for (int r=idx_start_row;r<idx_end_row;r++){
	// 	for (int c=idx_start_col;c<idx_end_col;c++){
	// 		// depthImage.at(r,c);
	// 	}
	// }
	return 0;
}



