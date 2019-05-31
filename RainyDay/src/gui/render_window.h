#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWidget>
#include "selectable_grid.h"
QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
QT_END_NAMESPACE

//! [0]
class RenderWindow : public QWidget{
    Q_OBJECT

public:
    RenderWindow();
    void setTitle(std::string title);
    void setRenderArea(SelectableGrid* ra);

private:
    SelectableGrid* _renderArea;
};

#endif // RENDERWINDOW_H
