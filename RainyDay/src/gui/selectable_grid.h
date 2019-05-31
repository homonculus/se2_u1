#ifndef SELECTABLEGRID_H
#define SELECTABLEGRID_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include "util.h"

// class RenderArea : public QWidget
// {
//     Q_OBJECT

// public:
//     QSize minimumSizeHint() const override;
//     QSize sizeHint() const override;

// private:
// };



class SelectableGrid : public QWidget
{
    Q_OBJECT

public:
    SelectableGrid();
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void setDimensions(int r, int c);
    void calculateCardSize();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    QPixmap pixmap;
    int n_rows;
    int n_cols;
    struct size _cell_size;
    struct size _card_size;
    struct point _card_indent;
    void setPen();
    void setBrush(int col, int row);
    void setTransformed(bool transformed);
};

#endif // SELECTABLEGRID_H
