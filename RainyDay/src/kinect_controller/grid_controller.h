#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H

#include <vector>
#include "kinect_controller.h"

enum GridCellStatus{GC_INACTIVE, GC_ACTIVE_1, GC_ACTIVE_2};

class GridController{
public:
	int n_cols;
	int n_rows;
	GridController(int _n_rows, int _n_cols);
	bool start();
	bool end();
	// std::vector<int> getCellActivity();

private:
	bool protonect_paused;
	std::vector<int> _grid;
	int _thresholdForCell(cv::Mat depthImage, int idx_start_row, int idx_end_row, int idx_start_col, int idx_end_col);

};

#endif // GRIDCONTROLLER_H
