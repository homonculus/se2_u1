#ifndef MEMORYPARAMWINDOW_H
#define MEMORYPARAMWINDOW_H


#include <QWidget>
#include <QtGui>
QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
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

    private slots:
        void rowChanged();
        void colChanged();

    private:
        MemoryCallibrationArea *callibrationArea;
        QLabel *rowLabel;
        QComboBox *rowComboBox;
        QLabel *colLabel;
        QComboBox *colComboBox;

        // QCheckBox *transformationsCheckBox;
};


#endif // MEMORYPARAMWINDOW_H