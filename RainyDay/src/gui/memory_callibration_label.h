#ifndef MEMORYCALLIBRATIONLABEL_H
#define MEMORYCALLIBRATIONLABEL_H

#include <QWidget>
#include <iostream>
#include <QLabel>
#include <QtGui>


class MemoryCallibrationLabel : public QLabel
{
    Q_OBJECT
 
public:
    ~MemoryCallibrationLabel();
 
protected slots:
 
    virtual void enterEvent ( QEvent *e );
    virtual void leaveEvent ( QEvent *e );
    virtual void mouseMoveEvent ( QMouseEvent *e );
    virtual void mousePressEvent ( QMouseEvent *e );
    virtual void mouseReleaseEvent ( QMouseEvent *e );
};

#endif // MEMORYCALLIBRATIONLABEL_H
