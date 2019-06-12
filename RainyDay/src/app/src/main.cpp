#include <QApplication>
#include "game.h"
#include "grid_controller.h"
#include "memory_controller.h"
#include <iostream>

#include "kinect_worker.h"
#include "kinect_timer.h"
#include <string>

#include <QWidget>


int main(int argc, char *argv[]){

    QApplication a(argc, argv);

	GridInfo dimensions = {5,3,15};

	MemoryController* m = new MemoryController();
	m->setDimensions(&dimensions);
	m->setContentPath("/Users/ahartens/Dropbox/Beuth/Semester_6/SE2/RainyDayProject/RainyDay/src/memory/content.csv");
	m->setupGame();
   	m->showWindow();
   	// m->startGame();

   	QThread* thread = new QThread;
   	KinectWorker *worker = new KinectWorker();
   	worker->moveToThread(thread);
	QObject::connect(thread, SIGNAL (started()), worker, SLOT (process()));
	QObject::connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
	QObject::connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
	QObject::connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
   	thread->start();
   	KinectTimer timer(m->getWindow());

    a.exec();
	return 0;
}


