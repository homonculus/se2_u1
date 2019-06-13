
#include "memory_game_window.h"
#include <string>
#include <QtWidgets>
#include <iostream>
#include <QApplication>
#include <QKeyEvent>


MemoryGameWindow::MemoryGameWindow(){

}

void MemoryGameWindow::setTitle(std::string title){
    setWindowTitle(tr("Basic Drawing"));
}

void MemoryGameWindow::setRenderArea(Grid* ra){

    _label = new QLabel("LABEL");

    _renderArea = ra;
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(_renderArea, 0, 0, 1, 4);
    mainLayout->addWidget(_label, 2, 0, Qt::AlignRight);

    setLayout(mainLayout);
}

// void MemoryGameWindow::keyPressEvent(QKeyEvent *event){
//     _label->setText(event->text());
//     delegate->MemoryGameWindowDidChange(event->key());
// }


void MemoryGameWindow::handleMyCustomEvent(const KinectEvent *event){
    // Now you can safely do something with your Qt objects.

    std::cout << "KinectEventWindow::handleMyCustomEvent : CUSTOM EVENT FIRED\n";

    // Access your custom data using event->getCustomData1() etc.
}