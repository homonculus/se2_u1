#ifndef KinectEventWindow_H
#define KinectEventWindow_H

#include <QWidget>

#include "kinect_event.h"
#include <opencv2/opencv.hpp>


class KinectEventWindow : public QWidget{
    Q_OBJECT

public:
	void postMyCustomEvent(const cv::Mat customData1, const cv::Mat customData2);
	virtual void handleMyCustomEvent(const KinectEvent *event) = 0;

protected:
    // void keyPressEvent(QKeyEvent *event);
	void customEvent(QEvent *event);

private:

};

#endif // KinectEventWindow_H
