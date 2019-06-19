#ifndef MEMORYCALLIBRATIONLABEL_H
#define MEMORYCALLIBRATIONLABEL_H

#include <QWidget>
#include <iostream>
#include <QLabel>
#include <QtGui>
#include <cmath>        // std::abs
#include <vector>


class MemoryCallibrationLabelDelegate{
    public:
        virtual void updateMemoryCallibrationLabelRects(int idx) = 0;
};

class MemoryCallibrationLabel : public QLabel
{
    Q_OBJECT
     
    public:
        ~MemoryCallibrationLabel();
        void createPoints();
        std::vector<QPoint*> getHandlePoints();
        MemoryCallibrationLabelDelegate *delegate;
        int idx;

    protected slots:
        virtual void enterEvent ( QEvent *e );
        virtual void leaveEvent ( QEvent *e );
        virtual void mouseMoveEvent ( QMouseEvent *e );
        virtual void mousePressEvent ( QMouseEvent *e );
        virtual void mouseReleaseEvent ( QMouseEvent *e );


    private:
        bool _dragging;
        std::vector<QPoint*> _points;
        std::vector<QPoint*> _points_outer;
        bool _pointIsWithinRadius(QPoint p1, QPoint p2, int r);
        int _draggingIdx;
};

#endif // MEMORYCALLIBRATIONLABEL_H
