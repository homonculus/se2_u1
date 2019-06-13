
#ifndef KINECTWORKER_H
#define KINECTWORKER_H

#include "kinect_controller.h"
#include <opencv2/opencv.hpp>
#include <QApplication>
#include <QObject>
#include "kinect_event_window.h"
#include <vector>


class KinectWorker : public QObject, public KinectControllerDelegate{
	    Q_OBJECT
	public:
	    KinectWorker(KinectEventWindow* window);
	    ~KinectWorker();
	    // void kinectControllerReceivedImage(cv::Mat* image);
		void kinectControllerReceivedImage(cv::Mat depth_image, cv::Mat registered_image);
	public slots:
	    void process();
	signals:
	    void finished();
	    void error(QString err);
	private:
		// KinectEventWindow *_window;
		std::vector<KinectEventWindow*> _windows;
		KinectController* _kinectController;
};

#endif // KINECTWORKER_H
