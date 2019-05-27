#ifndef KINECT_CONTROLLER_H
#define KINECT_CONTROLLER_H

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/registration.h>


class KinectControllerDelegate{
public:
	virtual int kinectController_imageReceived() = 0;

};

class KinectController{
public:
	int startDevice();
	void closeDevice();
	KinectControllerDelegate* delegate;

private:
	bool protonect_paused;
	libfreenect2::Freenect2Device* _dev;
	libfreenect2::Registration* _registration;
	void _getFrame();

};

#endif // KINECT_CONTROLLER_H
