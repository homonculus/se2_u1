#ifndef MEMORYCALLIBRATIONLABEL_H
#define MEMORYCALLIBRATIONLABEL_H

#include <QWidget>
#include <iostream>
#include <QLabel>
#include <QtGui>
#include <cmath>        // std::abs
#include <vector>
struct Point{
    int x;
    int y;
};

class CallibrationPoint{
    public:
        Point center;
        int idx;
        bool pointIsWithinRadius(Point p, int r){
            std::cout << "pointIsWithinRadius : center xy : " << center.x << ", " << center.y << " idx:" << idx << "\n";
            if ((std::abs(p.x - center.x)<r) && (std::abs(p.y-center.y)<r)){
                return true;
            }
            return false;
        }
    private:
};


class MemoryCallibrationLabel : public QLabel
{
    Q_OBJECT
     
    public:
        ~MemoryCallibrationLabel();
        void createPoints();
        std::vector<CallibrationPoint*>* getPoints();

    protected slots:
        virtual void enterEvent ( QEvent *e );
        virtual void leaveEvent ( QEvent *e );
        virtual void mouseMoveEvent ( QMouseEvent *e );
        virtual void mousePressEvent ( QMouseEvent *e );
        virtual void mouseReleaseEvent ( QMouseEvent *e );


    private:
        CallibrationPoint *_draggingPoint;
        bool _dragging;
        std::vector<CallibrationPoint*> _points;
        std::vector<CallibrationPoint*> _outerPoints;
        std::vector<QLabel*> _handles;
        std::vector<QLabel*> _outerHandles;
        QLabel *_draggingHandle;
        int _draggingIdx;
};

#endif // MEMORYCALLIBRATIONLABEL_H
