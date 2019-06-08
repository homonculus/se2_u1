#ifndef KINECTTIMER_H
#define KINECTTIMER_H

#include <QTimer>
#include <QEvent>
#include <kinect_timer_window.h>

class KinectTimer : public QObject{
	Q_OBJECT
	public:
		KinectTimer(KinectTimerWindow* window);
		QTimer *timer;

	public slots:
		void timerFired();

	private:
		KinectTimerWindow *_window;
		int values;
		void postEvent();
};


#endif // KINECTTIMER_H