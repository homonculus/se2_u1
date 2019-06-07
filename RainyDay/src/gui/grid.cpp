#include "grid.h"
#include "util.h"
#include <QPainter>
#include <iostream>

Grid::Grid(int r, int c){
    std::cout << "Grid::Grid 0\n";

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
    std::cout << "Grid::Grid 1\n";

}

void Grid::setCellsInfos(std::vector<GridCell*> ci){
    cellsInfo = ci;
}


QSize Grid::minimumSizeHint() const { return QSize(800, 800); }
QSize Grid::sizeHint() const { return QSize(800, 800); }

void Grid::paintEvent(QPaintEvent * /* event */){
    _calculateCardSize();
    QPainter painter(this);
    QFont font=painter.font();
    font.setPointSize(72);
    painter.setFont(font);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int i = 0;
    for (int r = 0; r < n_rows; r ++) {
        for (int c = 0; c < n_cols; c ++) {
            painter.save();
            painter.translate(c*_cell_size.width, r*_cell_size.height);
            this->_drawCard(&painter,cellsInfo[i]);
            painter.restore();
            i++;
        }
    }
}

void Grid::_calculateCardSize(){
    _cell_size.width =  width()/n_cols;
    _cell_size.height = height()/n_rows;
    _card_size.width = _cell_size.width - 2*_card_indent.x;
    _card_size.height = _cell_size.height - 2*_card_indent.y;
}

void Grid::_drawCard(QPainter *painter, GridCell* cellInfo){
    _setBrushColor(cellInfo->color);
    painter->setBrush(brush);
    QRect rect(_card_indent.x, _card_indent.y, _card_size.width, _card_size.height);
    painter->drawRoundedRect(rect, 10, 10, Qt::RelativeSize);


    // painter->drawText( QPoint(0,_card_size.height/2), cellInfo->text.c_str());
    
    const QRect rectangle = QRect(40, 0, _card_size.width, _card_size.height);
    QRect boundingRect;
    painter->drawText(rectangle, 0, cellInfo->text.c_str(), &boundingRect);

    //painter.drawRect(rect);
    //painter.drawPixmap(10, 10, pixmap);
}

void Grid::_drawFrame(QPainter *painter){
    // painter.setRenderHint(QPainter::Antialiasing, false);
    // painter.setPen(palette().dark().color());
    // painter.setBrush(Qt::NoBrush);
    // painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void Grid::_setPen(){
    Qt::PenStyle style = Qt::PenStyle(1);
    Qt::PenCapStyle cap = Qt::PenCapStyle(1);
    Qt::PenJoinStyle join = Qt::PenJoinStyle(1);
    this->pen = QPen(Qt::white, 0, style, cap, join);
}

void Grid::_setBrushColor(std::string s){
    QColor* color = new QColor(s.c_str());
    QLinearGradient linearGradient(0, 0, _card_size.height, _card_size.width);
    linearGradient.setColorAt(0.0, Qt::white);
    linearGradient.setColorAt(0.2, *color);
    linearGradient.setColorAt(1.0, Qt::black);
    this->brush = linearGradient;
}
