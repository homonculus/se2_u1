#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H

#include <vector>
#include "kinect_controller.h"

class GridControllerDelegate{
public:
	virtual void gridControllerDidChange(std::vector<int> cells) = 0;
};

class GridController: public KinectControllerDelegate{
public:
	int n_cols;
	int n_rows;
	GridController(int _n_rows, int _n_cols);
	int kinectControllerReceivedImage(cv::Mat depthImage);
	GridControllerDelegate* delegate;
	bool start();
	bool end();

private:
	KinectController* _kinectController;
	bool protonect_paused;
	std::vector<int> _grid;
	int _thresholdForCell(cv::Mat depthImage, int idx_start_row, int idx_end_row, int idx_start_col, int idx_end_col);

};

#endif // GRIDCONTROLLER_H
