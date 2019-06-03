#include "selectable_grid.h"
#include "util.h"
#include <QPainter>

#include <iostream>
SelectableGrid::SelectableGrid(int r, int c){
    antialiased = false;
    transformed = false;
    pixmap.load(":/images/qt-logo.png");

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    n_rows = r;
    n_cols = c;
    _card_indent.x = 5;
    _card_indent.y = 5;
    _setPen();
}

void SelectableGrid::setCellsInfos(std::vector<SelectableGridCell*> ci){
    cellsInfo = ci;
}


QSize SelectableGrid::minimumSizeHint() const { return QSize(800, 800); }
QSize SelectableGrid::sizeHint() const { return QSize(800, 800); }

void SelectableGrid::paintEvent(QPaintEvent * /* event */){
    _calculateCardSize();
    QPainter painter(this);
    QFont font=painter.font();
    font.setPointSize(72);
    painter.setFont(font);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int i = 0;
    for (int x = 0; x < n_cols; x ++) {
        for (int y = 0; y < n_rows; y ++) {
            painter.save();
            painter.translate(x*_cell_size.width, y*_cell_size.height);
            this->_drawCard(&painter,cellsInfo[i]);
            painter.restore();
            i++;
        }
    }
}

void SelectableGrid::_calculateCardSize(){
    _cell_size.width =  width()/n_cols;
    _cell_size.height = height()/n_rows;
    _card_size.width = _cell_size.width - 2*_card_indent.x;
    _card_size.height = _cell_size.height - 2*_card_indent.y;
}

void SelectableGrid::_drawCard(QPainter *painter, SelectableGridCell* cellInfo){
    std::string s = "#006266";
    _setBrushColor(cellInfo->color);
    painter->setBrush(brush);
    QRect rect(_card_indent.x, _card_indent.y, _card_size.width, _card_size.height);
    painter->drawRoundedRect(rect, 10, 10, Qt::RelativeSize);
    painter->drawText( QPoint(0,50), "HELLO THERE");
    //painter.drawRect(rect);
    //painter.drawPixmap(10, 10, pixmap);
}

void SelectableGrid::_drawFrame(QPainter *painter){
    // painter.setRenderHint(QPainter::Antialiasing, false);
    // painter.setPen(palette().dark().color());
    // painter.setBrush(Qt::NoBrush);
    // painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void SelectableGrid::_setPen(){
    Qt::PenStyle style = Qt::PenStyle(1);
    Qt::PenCapStyle cap = Qt::PenCapStyle(1);
    Qt::PenJoinStyle join = Qt::PenJoinStyle(1);
    this->pen = QPen(Qt::white, 0, style, cap, join);
}

void SelectableGrid::_setBrushColor(std::string s){
    QColor* color = new QColor(s.c_str());
    QLinearGradient linearGradient(0, 0, _card_size.height, _card_size.width);
    linearGradient.setColorAt(0.0, Qt::white);
    linearGradient.setColorAt(0.2, *color);
    linearGradient.setColorAt(1.0, Qt::black);
    this->brush = linearGradient;
}
