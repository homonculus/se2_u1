#include "memory_game_window.h"
#include <string>
#include <QtWidgets>
#include <iostream>
#include <QApplication>
#include <QKeyEvent>

void KinectEventWindow::postMyCustomEvent(const cv::Mat customData1, const cv::Mat customData2){   
    QApplication::postEvent(this, new KinectEvent(customData1, customData2));   
}

void KinectEventWindow::customEvent(QEvent *event){
 	handleMyCustomEvent((KinectEvent *)event);
}
