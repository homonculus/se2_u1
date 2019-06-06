#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWidget>
#include "selectable_grid.h"
#include <QtGui>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
QT_END_NAMESPACE


class RenderWindowDelegate{
public:
	virtual void renderWindowControllerDidChange(int e) = 0;
};

//! [0]
class RenderWindow : public QWidget{
    Q_OBJECT

public:
    RenderWindow();
    void setTitle(std::string title);
    void setRenderArea(SelectableGrid* ra);
	RenderWindowDelegate* delegate;

protected:
     void keyPressEvent(QKeyEvent *event);

private:
	QLabel *_label;
    SelectableGrid* _renderArea;
};

#endif // RENDERWINDOW_H
