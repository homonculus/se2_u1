#ifndef KINECT_CONTROLLER_H
#define KINECT_CONTROLLER_H

#include <libfreenect2/libfreenect2.hpp>

class KinectController{
public:
	KinectController(int n_rows, int n_cols);
	void print_dimensions();
	int startDevice();
	int closeDevice();

private:
	int n_rows;
    int n_cols; 
    bool protonect_paused;
};

#endif // KINECT_CONTROLLER_H
