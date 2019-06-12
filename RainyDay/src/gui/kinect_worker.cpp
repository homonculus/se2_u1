#include "kinect_worker.h"

#include <iostream>

KinectWorker::KinectWorker() { // Constructor
	std::cout << "kinect worker CONSTRUCTORS\n";

    // you could copy data from constructor arguments to internal variables here.
}

KinectWorker::~KinectWorker() { // Destructor
	std::cout << "kinect worker destructor\n";
    // free resources
}

void KinectWorker::process() { // Process. Start processing data.
    // allocate resources using new here

	_kinectController = new KinectController();
	_kinectController->startDevice();
	
 //    int i = 0;
	// while(i<1000000000){
	// 	if (i%1000000 == 0){
	// 		std::cout << "KinectWorker " << i << "\n";

	// 	}
	// 	i+= 1;
	// }
    // qDebug("Hello World!");
        // emit finished();
}
