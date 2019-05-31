#include "selectable_grid.h"
#include "util.h"
#include <QPainter>


SelectableGrid::SelectableGrid(QWidget *parent) : QWidget(parent){
    antialiased = false;
    transformed = false;
    pixmap.load(":/images/qt-logo.png");

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    n_rows = 4;
    n_cols = 5;
    _card_indent.x = 2;
    _card_indent.y = 2;
    setPen();
}

QSize SelectableGrid::minimumSizeHint() const {
    return QSize(800, 800);
}

QSize SelectableGrid::sizeHint() const {

    return QSize(800, 800);
}

void SelectableGrid::setPen(){
    Qt::PenStyle style = Qt::PenStyle(0);
    Qt::PenCapStyle cap = Qt::PenCapStyle(0);
    Qt::PenJoinStyle join = Qt::PenJoinStyle(0);
    this->pen = QPen(Qt::blue, 0, style, cap, join);
}

void SelectableGrid::setBrush(int col, int row){
    Qt::GlobalColor color = Qt::blue;
    if (col == 1 || row == 1){
       color = Qt::red;
    }

    QLinearGradient linearGradient(0, 0, _card_size.height, _card_size.width);
    linearGradient.setColorAt(0.0, Qt::white);
    linearGradient.setColorAt(0.2, color);
    linearGradient.setColorAt(1.0, Qt::black);
    this->brush = linearGradient;
//    update();
}

void SelectableGrid::setTransformed(bool transformed){
    this->transformed = transformed;
    update();
}

void SelectableGrid::calculateCardSize(){
    _cell_size.width =  width()/n_cols;
    _cell_size.height = height()/n_rows;
    _card_size.width = _cell_size.width - 2*_card_indent.x;
    _card_size.height = _cell_size.height - 2*_card_indent.y;

}

void SelectableGrid::paintEvent(QPaintEvent * /* event */){
    calculateCardSize();
    static const QPoint points[4] = {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70)
    };

    QRect rect(_card_indent.x, _card_indent.y, _card_size.width, _card_size.height);

    QPainter painter(this);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int x = 0; x < n_cols; x ++) {
        for (int y = 0; y < n_rows; y ++) {
            painter.save();

            setBrush(x,y);
            painter.setBrush(brush);
            painter.translate(x*_cell_size.width, y*_cell_size.height);

//            painter.drawRect(rect);
          painter.drawRoundedRect(rect, 10, 10, Qt::RelativeSize);
//          painter.drawPixmap(10, 10, pixmap);

            painter.restore();
        }
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

