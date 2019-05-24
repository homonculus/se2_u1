/// [headers]


#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>

#include <opencv2/opencv.hpp>

using namespace cv;


#include "kinect_controller.h"


KinectController::KinectController(int _n_rows, int _n_cols){
    n_rows = _n_rows;
    n_cols = _n_cols;
}

void KinectController::print_dimensions(){
  	std::cout << "kinect_controller : ("<<n_rows<<","<<n_cols<<")" << std::endl;
}



int KinectController::closeDevice(){

	return 0;
}

int KinectController::startDevice(){
 	libfreenect2::Freenect2Device *devtopause;
	bool protonect_shutdown = false; ///< Whether the running application should shut down.

 	/// [context]
	libfreenect2::Freenect2 freenect2;
	libfreenect2::Freenect2Device *dev = 0;
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
		dev = freenect2.openDevice(serial, pipeline);
		/// [open]
	}
	else{
		dev = freenect2.openDevice(serial);
	}
	if(dev == 0){
		std::cout << "failure opening device!" << std::endl;
		return -1;
	}

	devtopause = dev;

	
	/// [listeners]
	int types = 0;
	if (enable_rgb)
	types |= libfreenect2::Frame::Color;
	if (enable_depth)
	types |= libfreenect2::Frame::Ir | libfreenect2::Frame::Depth;
	libfreenect2::SyncMultiFrameListener listener(types);
	libfreenect2::FrameMap frames;

	dev->setColorFrameListener(&listener);
	dev->setIrAndDepthFrameListener(&listener);
	/// [listeners]

	/// [start]
	if (enable_rgb && enable_depth)
	{
	if (!dev->start())
	return -1;
	}
	else
	{
	if (!dev->startStreams(enable_rgb, enable_depth))
	return -1;
	}

	std::cout << "device serial: " << dev->getSerialNumber() << std::endl;
	std::cout << "device firmware: " << dev->getFirmwareVersion() << std::endl;
	/// [start]

	/// [registration setup]
	libfreenect2::Registration* registration = new libfreenect2::Registration(dev->getIrCameraParams(), dev->getColorCameraParams());
	libfreenect2::Frame undistorted(512, 424, 4), registered(512, 424, 4);
	/// [registration setup]

	size_t framecount = 0;
	#ifdef EXAMPLES_WITH_OPENGL_SUPPORT
	Viewer viewer;
	if (viewer_enabled)
	std::cout << "VIEWER IS ENABLED!" << std::endl;
	viewer.initialize();
	#else
	viewer_enabled = false;
	std::cout << "VIEWER IS NOOOOOOOOOOOOOT ENABLED!" << std::endl;

	#endif

	/// [loop start]
	while(!protonect_shutdown && (framemax == (size_t)-1 || framecount < framemax))
	{
	if (!listener.waitForNewFrame(frames, 10*1000)) // 10 sconds
	{
	std::cout << "timeout!" << std::endl;
	return -1;
	}
	libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
	libfreenect2::Frame *ir = frames[libfreenect2::Frame::Ir];
	libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];

	
	if (enable_rgb && enable_depth){
		registration->apply(rgb, depth, &undistorted, &registered);
	}

	Mat image = Mat(registered.height, registered.width, CV_8UC4, registered.data);

	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image",image);

	// Print the image matrix
	// std::cout << image << std::endl;

	waitKey(5);

	framecount++;
	/// [loop end]
	listener.release(frames);

	// break;
	/** libfreenect2::this_thread::sleep_for(libfreenect2::chrono::milliseconds(100)); */
	}

	std::cout << "HELLO THERE IAM TRYING TO BE HERE! 2" << std::endl;
	dev->stop();
	dev->close();

	delete registration;

	return 0;

}

