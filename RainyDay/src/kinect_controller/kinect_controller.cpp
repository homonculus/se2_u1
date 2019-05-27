#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>
#include "kinect_controller.h"

using namespace cv;


int KinectController::startDevice(){
	std::cout <<"KinectController::startDevice\n";
 	libfreenect2::Freenect2Device *devtopause;
	bool protonect_shutdown = false; ///< Whether the running application should shut down.

 	/// [context]
	libfreenect2::Freenect2 freenect2;
	libfreenect2::PacketPipeline *pipeline = 0;
	/// [context]

	std::string serial = "";
	bool viewer_enabled = true;
	bool enable_rgb = true;
	bool enable_depth = true;
	int deviceId = -1;
	size_t framemax = -1;

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
	devtopause = _dev;
	/// [listeners]
	int types = 0;
	if (enable_rgb)
	types |= libfreenect2::Frame::Color;
	if (enable_depth)
	types |= libfreenect2::Frame::Ir | libfreenect2::Frame::Depth;
	libfreenect2::SyncMultiFrameListener listener(types);
	libfreenect2::FrameMap frames;
	_dev->setColorFrameListener(&listener);
	_dev->setIrAndDepthFrameListener(&listener);
	/// [listeners]

	/// [start]
	if (enable_rgb && enable_depth){
		if (!_dev->start())
			return -1;
	}
	else{
	if (!_dev->startStreams(enable_rgb, enable_depth))
		return -1;
	}
	std::cout << "device serial: " << _dev->getSerialNumber() << std::endl;
	std::cout << "device firmware: " << _dev->getFirmwareVersion() << std::endl;
	/// [start]
	/// [registration setup]
	_registration = new libfreenect2::Registration(_dev->getIrCameraParams(), _dev->getColorCameraParams());
	libfreenect2::Frame undistorted(512, 424, 4), registered(512, 424, 4);
	/// [registration setup]
	size_t framecount = 0;

	/// [loop start]
	while(!protonect_shutdown && (framemax == (size_t)-1 || framecount < framemax)){
		if (!listener.waitForNewFrame(frames, 10*1000)){ // 10 sconds
			std::cout << "timeout!" << std::endl;
			return -1;
		}
		libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
		libfreenect2::Frame *ir = frames[libfreenect2::Frame::Ir];
		libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];
		if (enable_rgb && enable_depth){
			_registration->apply(rgb, depth, &undistorted, &registered);
		}
		Mat image = Mat(registered.height, registered.width, CV_8UC4, registered.data);
		Mat depth_image = Mat(depth->height, depth->width, CV_8UC4, depth->data);

		// namedWindow("Display Image", WINDOW_AUTOSIZE);
		// imshow("Display Image",depth_image);
		delegate->kinectControllerReceivedImage(depth_image);
		waitKey(5);
		framecount++;
		/// [loop end]
		listener.release(frames);

		// break;
		/** libfreenect2::this_thread::sleep_for(libfreenect2::chrono::milliseconds(100)); */
	}

	return 0;
}


void KinectController::closeDevice(){
	_dev->stop();
	_dev->close();
	delete _registration;
}

