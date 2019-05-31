#include "game.h"
#include "grid_controller.h"
#include "memory_controller.h"
#include <iostream>

int main(int argc, char *argv[]){
	GridInfo dimensions = {3,3,9};

	MemoryController* m = new MemoryController();
	m->setDimensions(&dimensions);
	m->setContentPath("./content.csv");
	m->setupGame();
	m->startGame();

    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // a.exec();
	return 0;
}
