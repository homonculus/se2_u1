

#ifndef KINECTTIMER_H
#define KINECTTIMER_H

#include <QTimer>
#include <QEvent>
#include <render_window.h>

class KinectTimer : public QObject{
	Q_OBJECT
	public:
		KinectTimer(RenderWindow* window);
		QTimer *timer;

	public slots:
		void timerFired();

	private:
		RenderWindow *_window;
		int values;
		void postEvent();
};


#endif // KINECTTIMER_H