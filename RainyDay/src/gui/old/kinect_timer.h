#ifndef KINECTTIMER_H
#define KINECTTIMER_H

#include <QTimer>
#include <QEvent>
#include <memory_game_window.h>

class KinectTimer : public QObject{
	Q_OBJECT
	public:
		KinectTimer(KinectEventWindow* window);
		QTimer *timer;

	public slots:
		void timerFired();

	private:
		KinectEventWindow *_window;
		int values;
		void postEvent();
};


#endif // KINECTTIMER_H