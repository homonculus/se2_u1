#include <QApplication>
#include "mainwindow.h"
#include "kinect_controller.h"
#include <iostream>

int main(int argc, char *argv[]){

	KinectController my_controller(4,4);
  	std::cout << "HELLO THERE IAM TRYING TO BE HERE! 1" << std::endl;
  	my_controller.print_dimensions();

  	my_controller.startDevice();
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
    return 0;

}
