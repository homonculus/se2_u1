#include "kinect_timer.h"
#include <QDebug>
#include <QApplication>

KinectTimer::KinectTimer(RenderWindow* window){
	_window = window;
	timer = new QTimer(this);

	connect(timer,SIGNAL(timeout()), this, SLOT(timerFired()));

	values = 0;
	timer->start(1000);


}

void KinectTimer::timerFired(){
	values += 1;
	qDebug() << "Timer.." << values;
	_window->postMyCustomEvent(values,0);
}

//https://stackoverflow.com/questions/6061352/creating-a-custom-message-event-with-qt