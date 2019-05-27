
#include <libfreenect2/logger.h>
#include <opencv2/opencv.hpp>
#include "kinect_controller.h"

using namespace cv;


int KinectController::startDevice(){
	std::cout <<"KinectController::startDevice\n";
	shutdown = false; ///< Whether the running application should shut down.
 	/// [context]
	libfreenect2::Freenect2 freenect2;
	libfreenect2::PacketPipeline *pipeline = 0;
	/// [context]

	std::string serial = "";
	bool viewer_enabled = true;
	bool enable_rgb = true;
	bool enable_depth = true;
	int deviceId = -1;

	/// [discovery]
	if(freenect2.enumerateDevices() == 0) {
		std::cout << "no device connected!" << std::endl;
		return -1;
	}
	if (serial == "") {
		serial = freenect2.getDefaultDeviceSerialNumber();
	}
	/// [discovery]
	if(pipeline){
		/// [open]
		_dev = freenect2.openDevice(serial, pipeline);
		/// [open]
	}
	else{
		_dev = freenect2.openDevice(serial);
	}
	if(_dev == 0){
		std::cout << "failure opening device!" << std::endl;
		return -1;
	}


	
	/// [listeners]
	int types = 0;
	types |= libfreenect2::Frame::Color;
	types |= libfreenect2::Frame::Ir | libfreenect2::Frame::Depth;
	libfreenect2::SyncMultiFrameListener _listener(types);
	libfreenect2::FrameMap frames;

	_dev->setColorFrameListener(&_listener);
	_dev->setIrAndDepthFrameListener(&_listener);
	/// [listeners]

	if (!_dev->startStreams(enable_rgb, enable_depth)){
		return -1;
	}

	std::cout << "device serial: " << _dev->getSerialNumber() << std::endl;
	std::cout << "device firmware: " << _dev->getFirmwareVersion() << std::endl;
	/// [start]

	/// [registration setup]
	_registration = new libfreenect2::Registration(_dev->getIrCameraParams(), _dev->getColorCameraParams());
	/// [registration setup]
	_getFrame();
	return 0;
}

int KinectController::_getFrame(){
	size_t framecount = 0;
	size_t framemax = -1;
	libfreenect2::Frame _undistorted(512, 424, 4), _registered(512, 424, 4);

	/// [loop start]
	while(!shutdown && (framemax == (size_t)-1 || framecount < framemax)){
		if (!_listener->waitForNewFrame(_frames, 10*1000)){ // 10 sconds
			std::cout << "timeout!" << std::endl;
			return -1;
		}
		libfreenect2::Frame *rgb = _frames[libfreenect2::Frame::Color];
		libfreenect2::Frame *ir = _frames[libfreenect2::Frame::Ir];
		libfreenect2::Frame *depth = _frames[libfreenect2::Frame::Depth];

		
		_registration->apply(rgb, depth, &_undistorted, &_registered);
		Mat image = Mat(_registered.height, _registered.width, CV_8UC4, _registered.data);
		Mat depthImage = Mat(depth->height, depth->width, CV_8UC4, depth->data);

		namedWindow("Display Image", WINDOW_AUTOSIZE);
		imshow("Display Image",depthImage);


		// delegate->kinectControllerReceivedImage();

		// Print the image matrix
		// std::cout << image << std::endl;

		waitKey(5);

		framecount++;
		/// [loop end]
		_listener->release(_frames);

		break;
		/** libfreenect2::this_thread::sleep_for(libfreenect2::chrono::milliseconds(100)); */
	}
	return 0;
}

void KinectController::closeDevice(){
	_dev->stop();
	_dev->close();
	delete _registration;
}

