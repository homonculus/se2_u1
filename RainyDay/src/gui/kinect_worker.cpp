#include "kinect_worker.h"

#include <iostream>
#include "kinect_event.h"

KinectWorker::KinectWorker(KinectEventWindow* window) {
	std::cout << "kinect worker CONSTRUCTORS\n";
	_windows.push_back(window);
}

KinectWorker::~KinectWorker() {
	std::cout << "kinect worker destructor\n";
}

void KinectWorker::process() {
	_kinectController = new KinectController();
	_kinectController->delegate = this;
	_kinectController->startDevice();
    // emit finished();
}


void KinectWorker::kinectControllerReceivedImage(cv::Mat depth_image, cv::Mat registered_image){
	for (int i = 0;i<_windows.size();i++){
		_windows[i]->postMyCustomEvent(depth_image,registered_image);
	}
}