#include <QApplication>
#include "mainwindow.h"
#include "game.h"
#include "grid_controller.h"
#include "memory_controller.h"
#include <iostream>

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

	GridInfo dimensions = {3,3,9};

	MemoryController* m = new MemoryController();
	m->setDimensions(&dimensions);
	m->setContentPath("./content.csv");
	m->setupGame();

   	m->showWindow();

   	while (true){
   		std::cout <<"hellow\n";
   	}
    a.exec();
	return 0;
}
