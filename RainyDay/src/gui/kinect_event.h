#ifndef KINECTEVENT_H
#define KINECTEVENT_H

#include <QWidget>
#include <QtWidgets>
#include <QApplication>
#include <QKeyEvent>
#include <opencv2/opencv.hpp>

class KinectEvent : public QEvent{
	public:
		KinectEvent(const cv::Mat customData1, const cv::Mat customData2):QEvent((QEvent::Type)2000), m_customData1(customData1),m_customData2(customData2){}
		cv::Mat getCustomData1() const{ return m_customData1; }
		cv::Mat getCustomData2() const{ return m_customData2; }

	private:
		cv::Mat m_customData1;
		cv::Mat m_customData2;
};



// class KinectEvent : public QEvent{
// 	public:
// 		KinectEvent(const int width, const int height, const unsigned char *data):QEvent((QEvent::Type)2000), m_width(width),m_height(height), m_data(data){}
// 		int getCustomData1() const{ return m_customData1; }
// 		int getCustomData2() const{ return m_customData2; }

// 	private:
// 		int m_width;
// 		int m_height;
// 		int m_data;
// };




// class KinectEvent : public QEvent{
// 	public:
// 		KinectEvent(const int customData1, const int customData2):QEvent((QEvent::Type)2000), m_customData1(customData1),m_customData2(customData2){}
// 		int getCustomData1() const{ return m_customData1; }
// 		int getCustomData2() const{ return m_customData2; }

// 	private:
// 		int m_customData1;
// 		int m_customData2;
// };


#endif // KINECTEVENT_H