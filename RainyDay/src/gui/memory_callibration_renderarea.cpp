#include "memory_callibration_renderarea.h"

#include <QPainter>

MemoryCallibrationRenderArea::MemoryCallibrationRenderArea(){
    this->antialiased = true;;
    // setBackgroundRole(QPalette::Base);
    // setAutoFillBackground(true);

 // setAttribute(Qt::WA_NoSystemBackground);
 //    setAttribute(Qt::WA_TranslucentBackground);
 //    setAttribute(Qt::WA_PaintOnScreen);

    setAttribute(Qt::WA_TransparentForMouseEvents);


    static const QPoint points[4] = {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70)
    };
    _points = points;
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

void MemoryCallibrationRenderArea::updatePoints(const QPoint *points){
    static const QPoint points[4] = {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70)
    };
    _points = points;
    update();
}

void MemoryCallibrationRenderArea::paintEvent(QPaintEvent * /* event */){
    // static const QPoint points[4] = {
    //     QPoint(10, 80),
    //     QPoint(20, 10),
    //     QPoint(80, 30),
    //     QPoint(90, 70)
    // };

    // QPainterPath path;
    // path.moveTo(20, 80);
    // path.lineTo(20, 30);
    // path.cubicTo(80, 0, 50, 50, 80, 80);


    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int x = 0; x < width(); x += 100) {
        for (int y = 0; y < height(); y += 100) {
            painter.save();
            painter.translate(x, y);
            if (transformed) {
                painter.translate(50, 50);
                painter.rotate(60.0);
                painter.scale(0.6, 0.9);
                painter.translate(-50, -50);
            }

            painter.drawPolygon(_points, 4);
            
            painter.restore();
            break;
        }
        break;
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}