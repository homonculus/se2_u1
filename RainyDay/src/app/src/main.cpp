#include <QApplication>
#include "mainwindow.h"
#include "game.h"
#include "grid_controller.h"
#include "memory_controller.h"
#include <iostream>

#include "kinect_timer.h"

#include <string>

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

	GridInfo dimensions = {5,3,15};

	MemoryController* m = new MemoryController();
	m->setDimensions(&dimensions);
	m->setContentPath("/Users/ahartens/Dropbox/Beuth/Semester_6/SE2/RainyDayProject/RainyDay/src/memory/content.csv");
	m->setupGame();
   	m->showWindow();
   	m->startGame();

   	KinectTimer timer(m->getWindow());

    a.exec();
	return 0;
}
