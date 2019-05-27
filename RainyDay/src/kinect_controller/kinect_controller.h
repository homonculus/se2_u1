#ifndef KINECT_CONTROLLER_H
#define KINECT_CONTROLLER_H

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/registration.h>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/packet_pipeline.h>


class KinectControllerDelegate{
public:
	virtual int kinectControllerReceivedImage() = 0;

};

class KinectController{
public:
	int startDevice();
	void closeDevice();
	KinectControllerDelegate* delegate;
	bool shutdown;

private:
	bool protonect_paused;
	libfreenect2::Freenect2Device* _dev;
	libfreenect2::Registration* _registration;
	libfreenect2::SyncMultiFrameListener* _listener;
	libfreenect2::FrameMap _frames;
	int _getFrame();

};

#endif // KINECT_CONTROLLER_H
