#ifndef KinectTimerWindow_H
#define KinectTimerWindow_H

#include <QWidget>
#include "grid.h"
#include <QtGui>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
QT_END_NAMESPACE

class KinectTimerEvent : public QEvent{
	public:
		KinectTimerEvent(const int customData1, const int customData2):QEvent((QEvent::Type)2000), m_customData1(customData1),m_customData2(customData2){}
		int getCustomData1() const{ return m_customData1; }
		int getCustomData2() const{ return m_customData2; }

	private:
		int m_customData1;
		int m_customData2;
};

class KinectTimerWindowDelegate{
public:
	virtual void KinectTimerWindowControllerDidChange(int e) = 0;
};

//! [0]
class KinectTimerWindow : public QWidget{
    Q_OBJECT

public:
    KinectTimerWindow();
    void setTitle(std::string title);
    void setRenderArea(Grid* ra);
	KinectTimerWindowDelegate* delegate;
	void postMyCustomEvent(const int customData1, const int customData2);
	void handleMyCustomEvent(const KinectTimerEvent *event);

protected:
    void keyPressEvent(QKeyEvent *event);
	void customEvent(QEvent *event);

private:
	QLabel *_label;
    Grid* _renderArea;
};

#endif // KinectTimerWindow_H
