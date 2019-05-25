#include <QApplication>
#include "mainwindow.h"
#include "kinect_controller.h"
#include "team_controller.h"
#include "memory_controller.h"
#include <iostream>

int main(int argc, char *argv[]){

	// KinectController my_controller(4,4);
 //  	std::cout << "HELLO THERE IAM TRYING TO BE HERE! 1" << std::endl;
 //  	my_controller.print_dimensions();

  	// my_controller.startDevice();



	TeamController* tc = new TeamController(3,3);

	MemoryController* m = new MemoryController();
	m->setDimensions(3,3);
	m->setContentPath("./content.csv");
	m->setupGame();

	while(!m->gameIsOver()){



	}

    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // a.exec();
	return 0;
}
