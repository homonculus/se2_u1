#ifndef KINECT_CONTROLLER_H
#define KINECT_CONTROLLER_H

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/registration.h>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/packet_pipeline.h>
#include <opencv2/opencv.hpp>


class KinectController{
public:
	int startDevice();
	cv::Mat getDepthImage();
	void closeDevice();
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
