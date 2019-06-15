#ifndef MEMORYCALLIBRATIONRENDERAREA_H
#define MEMORYCALLIBRATIONRENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <vector>

class MemoryCallibrationRenderArea : public QWidget
{
    Q_OBJECT

public:
    MemoryCallibrationRenderArea();
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    void _setPen(const QPen &pen);
    void _setBrush(const QBrush &brush);
    const QPoint * _points;
    void updatePoints(const QPoint *points);
};

#endif // MEMORYCALLIBRATIONRENDERAREA_H