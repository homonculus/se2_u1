#ifndef MEMORYCALLIBRATIONRENDERAREA_H
#define MEMORYCALLIBRATIONRENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <vector>
#include "memory_grid_cell_manager.h"

class MemoryCallibrationRenderArea : public QWidget
{
    Q_OBJECT

public:
    MemoryCallibrationRenderArea();
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void updatePoints(std::vector<QPoint*> points);
    void setGridCells(std::vector<MemoryGridCell*> points);
    std::vector<std::vector<QPoint*> > getGridPoints(){return _gridpoints;};

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    void _setPen(const QPen &pen);
    void _setBrush(const QBrush &brush);
    void _drawGrid(QPainter *painter);
    std::vector<QPoint*> _points;
    int _drawGridFlag;
    std::vector<std::vector<QPoint*> > _gridpoints;
    std::vector<MemoryGridCell*> _gridcells;

};

#endif // MEMORYCALLIBRATIONRENDERAREA_H