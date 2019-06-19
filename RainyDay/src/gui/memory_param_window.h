#ifndef MEMORYPARAMWINDOW_H
#define MEMORYPARAMWINDOW_H


#include "kinect_event_window.h"
#include <QWidget>
#include <QtGui>
#include "memory_callibration_label.h"
#include "memory_callibration_renderarea.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
class QGroupBox;
class QPushButton;

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

struct RGB {
    uchar blue;
    uchar green;
    uchar red;  };


class MemoryParamWindow : public KinectEventWindow, public MemoryCallibrationLabelDelegate{
    Q_OBJECT
    public:
        MemoryParamWindow();
        void setCallibrationImage(cv::Mat mat);
        void handleMyCustomEvent(const KinectEvent *event);
        void updateMemoryCallibrationLabelRects(int idx);

    private slots:
        void rowChanged();
        void colChanged();
        void handleStartButton();

    private:
        MemoryCallibrationArea *callibrationArea;
        QLabel *_rowLabel;
        QComboBox *_rowComboBox;
        QLabel *_colLabel;
        QComboBox *_colComboBox;
        QGroupBox *_dimensionsBox;
        QGroupBox *_callibrationBox;
        QGroupBox *_buttonBox;
        QPushButton *_buttonStart;
        QPushButton *_buttonStop;
        MemoryCallibrationLabel *_callibrationLabel1;
        MemoryCallibrationLabel *_callibrationLabel2;
        MemoryCallibrationRenderArea *_callibrationRenderArea1;
        MemoryCallibrationRenderArea *_callibrationRenderArea2;
        void _createDimensionsBox();
        void _createCallibrationBox();
        void _createControlBox();
        void _drawCallibrationPointsIn(cv::Mat);
        void _drawPointInMat(int p_x, int p_y, cv::Mat mat);
        void _drawGridInCallibrationLabel();
    std::vector<cv::Point2f> _convertQPointsToCVPoints(std::vector<QPoint*> p);

        // QCheckBox *transformationsCheckBox;
};


#endif // MEMORYPARAMWINDOW_H