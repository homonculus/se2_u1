#ifndef KINECT_CONTROLLER_H
#define KINECT_CONTROLLER_H

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/registration.h>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/packet_pipeline.h>
#include <opencv2/opencv.hpp>


struct KinectImage{
	unsigned char *data;
	int width;
	int height;
};


class KinectControllerDelegate{
	public:
		virtual void kinectControllerReceivedImage(cv::Mat depth_image, cv::Mat registered_image) = 0;
		// virtual void kinectControllerReceivedImage(cv::Mat* image) = 0;
};


class KinectController{
public:
	int startDevice();
	KinectImage* getDepthImage();
	void closeDevice();
	bool shutdown;
	KinectControllerDelegate *delegate;

private:
	bool protonect_paused;
	libfreenect2::Freenect2Device* _dev;
	libfreenect2::Registration* _registration;
	// libfreenect2::SyncMultiFrameListener* _listener;
	libfreenect2::FrameMap _frames;
	int _getFrame();
	KinectImage *_image;
	libfreenect2::FrameMap frames;
	libfreenect2::FrameListener *myListener;
 	// libfreenect2::Freenect2Device *devtopause;
	// libfreenect2::SyncMultiFrameListener listener(3);

};

#endif // KINECT_CONTROLLER_H
