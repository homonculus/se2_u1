#include "memory_callibration_renderarea.h"

#include <QPainter>
#include <iostream>

MemoryCallibrationRenderArea::MemoryCallibrationRenderArea(){
    this->antialiased = true;;
    setAttribute(Qt::WA_TransparentForMouseEvents);

    for (int i =0;i<4;i++){
        QPoint p = QPoint(0,0);
        _points.push_back(&p);
    }
    _drawGridFlag = false;

    std::vector<QPoint *> gpoints;
    gpoints.push_back(new QPoint(0,100));
    gpoints.push_back(new QPoint(100,100));
    gpoints.push_back(new QPoint(0,200));
    gpoints.push_back(new QPoint(100,200));
    _gridpoints.push_back(gpoints);
}

QSize MemoryCallibrationRenderArea::minimumSizeHint() const{
    return QSize(100, 100);
}

QSize MemoryCallibrationRenderArea::sizeHint() const{
    return QSize(400, 200);
}

void MemoryCallibrationRenderArea::_setPen(const QPen &pen){
    this->pen = pen;
    update();
}

void MemoryCallibrationRenderArea::_setBrush(const QBrush &brush){
    this->brush = brush;
    update();
}

void MemoryCallibrationRenderArea::updatePoints(std::vector<QPoint*> points){
    _points = points;
    std::cout << "UPDATING UPOINTS!!!\n";
    update();
}

void MemoryCallibrationRenderArea::paintEvent(QPaintEvent * /* event */){
    QPoint points[4] = {
        *_points[0],
        *_points[2],
        *_points[3],
        *_points[1],
    };

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing, true);


    painter.save();
    painter.translate(0, 0);


    painter.drawPolygon(points, 4);

    if (_drawGridFlag){
        std::cout << "MemoryCallibrationRenderArea::paintEvent with draw grid\n";
        painter.setBrush(QColor(30, 30, 30, 100));
        painter.setPen(QColor(255, 0, 0, 255));
        _drawGrid(&painter);
    }
    else{
        std::cout << "MemoryCallibrationRenderArea::paintEvent with NO DRAW grid\n";
        painter.setBrush(Qt::cyan);
        painter.setPen(Qt::darkCyan);

        for (int i=0;i<_points.size();i++){
            painter.drawEllipse(*_points[i],10,10);

        }
    }
    
    painter.restore();
}

void MemoryCallibrationRenderArea::setGridPoints(std::vector<std::vector<QPoint*> > points){
    _drawGridFlag = true;
    _gridpoints = points;
    std::cout << "MemoryCallibrationRenderArea::setGridPoints\n";
}

void MemoryCallibrationRenderArea::_drawGrid(QPainter *painter){

    std::cout << "MemoryCallibrationRenderArea::_drawGrid  size : "<< _gridpoints.size();

    for (int i=0;i<_gridpoints.size();i++){
        std::cout << "MemoryCallibrationRenderArea::_drawGrid 1\n";
        QPoint points[4] = {
            *_gridpoints[i][0],
            *_gridpoints[i][2],
            *_gridpoints[i][3],
            *_gridpoints[i][1],
        };

        std::cout << "MemoryCallibrationRenderArea::_drawGrid 2\n";
        painter->drawPolygon(points,4);
    }
}