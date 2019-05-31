
#include "render_window.h"
#include <string>
#include <QtWidgets>

RenderWindow::RenderWindow(){
        setWindowTitle(tr("Basic Drawing"));

}

void RenderWindow::setTitle(std::string title){
    setWindowTitle(tr("Basic Drawing"));
}

void RenderWindow::setRenderArea(SelectableGrid* ra){
    _renderArea = ra;
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(_renderArea, 0, 0, 1, 4);
    setLayout(mainLayout);
}