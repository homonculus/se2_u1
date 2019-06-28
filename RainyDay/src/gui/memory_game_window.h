#ifndef MEMORYGAMEWINDOW_H
#define MEMORYGAMEWINDOW_H

#include <QWidget>
#include "grid.h"
#include <QtGui>
#include "kinect_event_window.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
QT_END_NAMESPACE



//! [0]
class MemoryGameWindow : public KinectEventWindow{
    Q_OBJECT

public:
    MemoryGameWindow();
    void setTitle(std::string title);
    void setRenderArea(Grid* ra);
	void handleMyCustomEvent(const KinectEvent *event);
	// void postMyCustomEvent(const int customData1, const int customData2);
	// void handleMyCustomEvent(const KinectEvent *event);

// protected:
//     void keyPressEvent(QKeyEvent *event);
// 	void customEvent(QEvent *event);

private:
	QLabel *_label;
    Grid* _renderArea;
};

#endif // MEMORYGAMEWINDOW_H
