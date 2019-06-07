
#include "kinect_timer_window.h"
#include <string>
#include <QtWidgets>
#include <iostream>
#include <QApplication>
#include <QKeyEvent>


KinectTimerWindow::KinectTimerWindow(){
        setWindowTitle(tr("Basic Drawing"));

}

void KinectTimerWindow::setTitle(std::string title){
    setWindowTitle(tr("Basic Drawing"));
}

void KinectTimerWindow::setRenderArea(Grid* ra){

    _label = new QLabel("LABEL");

    _renderArea = ra;
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(_renderArea, 0, 0, 1, 4);
    mainLayout->addWidget(_label, 2, 0, Qt::AlignRight);

    setLayout(mainLayout);
}


void KinectTimerWindow::keyPressEvent(QKeyEvent *event){
    _label->setText(event->text());
    delegate->KinectTimerWindowControllerDidChange(event->key());

 }


 void KinectTimerWindow::postMyCustomEvent(const int customData1, const int customData2)
{   
    // This method (postMyCustomEvent) can be called from any thread

    QApplication::postEvent(this, new KinectTimerEvent(customData1, customData2));   
}

void KinectTimerWindow::customEvent(QEvent * event)
{
    // When we get here, we've crossed the thread boundary and are now
    // executing in the Qt object's thread

 	std::cout << "CUSTOM EVENT FIRED\n";


    // use more else ifs to handle other custom events
}

void KinectTimerWindow::handleMyCustomEvent(const KinectTimerEvent *event)
{
    // Now you can safely do something with your Qt objects.
    // Access your custom data using event->getCustomData1() etc.
}