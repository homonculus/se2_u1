
#include "render_window.h"
#include <string>
#include <QtWidgets>
#include <iostream>
#include <QApplication>
#include <QKeyEvent>


RenderWindow::RenderWindow(){
        setWindowTitle(tr("Basic Drawing"));

}

void RenderWindow::setTitle(std::string title){
    setWindowTitle(tr("Basic Drawing"));
}

void RenderWindow::setRenderArea(SelectableGrid* ra){

    _label = new QLabel("LABEL");

    _renderArea = ra;
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(_renderArea, 0, 0, 1, 4);
    mainLayout->addWidget(_label, 2, 0, Qt::AlignRight);

    setLayout(mainLayout);
}


void RenderWindow::keyPressEvent(QKeyEvent *event){
    _label->setText(event->text());
    delegate->renderWindowControllerDidChange(event->key());

 }