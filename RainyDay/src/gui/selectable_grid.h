#ifndef SELECTABLEGRID_H
#define SELECTABLEGRID_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <string>
#include <vector>
#include "util.h"


struct SelectableGridCell{
    std::string color;
    std::string text;
};

class SelectableGrid : public QWidget
{
    Q_OBJECT

public:
    SelectableGrid(int r, int c);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void setDimensions(int r, int c);
    void setCellsInfos(std::vector<SelectableGridCell*> ci);
    std::vector<SelectableGridCell*> cellsInfo;

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
    void _calculateCardSize();
    void _drawCard(QPainter *painter, SelectableGridCell* cellInfo);
    void _setBrushColor(std::string s);
    void _setPen();
    void _drawFrame(QPainter *painter);
};

#endif // SELECTABLEGRID_H
