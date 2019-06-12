#ifndef MEMORYPARAMWINDOW_H
#define MEMORYPARAMWINDOW_H


#include <QWidget>
#include <QtGui>
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


class MemoryParamWindow : public QWidget{
    Q_OBJECT
    public:
        MemoryParamWindow();
        void setCallibrationImage(unsigned char* data, int width, int height);

    private slots:
        void rowChanged();
        void colChanged();

    private:
        MemoryCallibrationArea *callibrationArea;
        QLabel *_rowLabel;
        QComboBox *_rowComboBox;
        QLabel *_colLabel;
        QComboBox *_colComboBox;
        QGroupBox *_dimensionsBox;
        QGroupBox *_callibrationBox;
        QLabel *_callibrationLabel;
        void _createDimensionsBox();
        void _createCallibrationBox();

        // QCheckBox *transformationsCheckBox;
};


#endif // MEMORYPARAMWINDOW_H