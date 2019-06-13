#ifndef MEMORYPARAMWINDOW_H
#define MEMORYPARAMWINDOW_H


#include "kinect_event_window.h"
#include <QWidget>
#include <QtGui>
#include "memory_callibration_label.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
class QGroupBox;

QT_END_NAMESPACE

class MemoryCallibrationArea : public QWidget{
    Q_OBJECT

public:
    QSize minimumSizeHint() const override{
    return QSize(100, 100);
}
    QSize sizeHint() const override{
    return QSize(400, 200);
}
    
private:
};


class MemoryParamWindow : public KinectEventWindow{
    Q_OBJECT
    public:
        MemoryParamWindow();
        void setCallibrationImage(cv::Mat mat);
        void handleMyCustomEvent(const KinectEvent *event);

    private slots:
        void rowChanged();
        void colChanged();

    // protected :
    //     void mouseMoveEvent(QMouseEvent *e);
    //     void mouseReleaseEvent(QMouseEvent *e);
    //     void mouseDoubleClickEvent(QMouseEvent *e);
    //     void mousePressEvent(QMouseEvent *e);
    //     void keyPressEvent(QKeyEvent *event);

    private:
        MemoryCallibrationArea *callibrationArea;
        QLabel *_rowLabel;
        QComboBox *_rowComboBox;
        QLabel *_colLabel;
        QComboBox *_colComboBox;
        QGroupBox *_dimensionsBox;
        QGroupBox *_callibrationBox;
        MemoryCallibrationLabel *_callibrationLabel;
        void _createDimensionsBox();
        void _createCallibrationBox();

        // QCheckBox *transformationsCheckBox;
};


#endif // MEMORYPARAMWINDOW_H