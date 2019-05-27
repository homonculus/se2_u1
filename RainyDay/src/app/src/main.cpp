#include <QApplication>
#include "mainwindow.h"
#include "kinect_controller.h"
#include "game.h"
#include "team_controller.h"
#include "memory_controller.h"
#include <iostream>

int main(int argc, char *argv[]){

	// KinectController my_controller(4,4);
 //  	std::cout << "HELLO THERE IAM TRYING TO BE HERE! 1" << std::endl;
 //  	my_controller.print_dimensions();

  	// my_controller.startDevice();

	GridInfo dimensions = {3,3,9};

	TeamController* tc = new TeamController(&dimensions);

	MemoryController* m = new MemoryController();
	m->setDimensions(&dimensions);
	m->setContentPath("./content.csv");
	m->setupGame();

	tc->delegate = m;
	tc->start();


	// while(!m->gameIsOver()){



	// }

    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // a.exec();
	return 0;
}
