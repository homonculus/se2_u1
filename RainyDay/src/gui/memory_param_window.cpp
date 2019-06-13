#include "memory_param_window.h"
#include <iostream>
#include <QtWidgets>


const int IdRole = Qt::UserRole;

MemoryParamWindow::MemoryParamWindow()
{
    setWindowTitle(tr("Memory Parameters"));

    _createDimensionsBox();
    _createCallibrationBox();
    connect(_rowComboBox, SIGNAL(activated(int)), this, SLOT(rowChanged()));
    connect(_colComboBox, SIGNAL(activated(int)), this, SLOT(colChanged()));

    // QGridLayout *mainLayout = new QGridLayout;
    // mainLayout->setColumnStretch(3, 1);
    // mainLayout->addWidget(_rowLabel,0,0,Qt::AlignRight);// row column
    // mainLayout->addWidget(_rowComboBox,0,1);

    // mainLayout->addWidget(_colLabel,1,0,Qt::AlignRight);
    // mainLayout->addWidget(_colComboBox,1,1);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(_dimensionsBox,0,0);// row column
    mainLayout->addWidget(_callibrationBox,1,0);
    this->setMouseTracking(true);
    // mainLayout->addWidget(_colLabel,1,0,Qt::AlignRight);
    // mainLayout->addWidget(_colComboBox,1,1);

    setLayout(mainLayout);
}

void MemoryParamWindow::_createDimensionsBox(){
    _dimensionsBox = new QGroupBox(tr("Spiel Dimensionen"));
    
    _rowComboBox = new QComboBox;
    _rowComboBox->addItem(tr("2"),0);
    _rowComboBox->addItem(tr("3"),1);
    _rowComboBox->addItem(tr("4"),2);
    _rowComboBox->addItem(tr("5"),2);
    _rowLabel = new QLabel(tr("&Anzahl Reien:"));
    _rowLabel->setBuddy(_rowComboBox);

    _colComboBox = new QComboBox;
    _colComboBox->addItem(tr("2"),0);
    _colComboBox->addItem(tr("3"),1);
    _colComboBox->addItem(tr("4"),2);
    _colComboBox->addItem(tr("5"),2);
    _colLabel = new QLabel(tr("&Anzahl Spalten:"));
    _colLabel->setBuddy(_colComboBox);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(_rowLabel,0,0,Qt::AlignRight);// row column
    layout->addWidget(_rowComboBox,0,1);
    layout->addWidget(_colLabel,1,0,Qt::AlignRight);
    layout->addWidget(_colComboBox,1,1);
    layout->setColumnStretch(1, 10);

    _dimensionsBox->setLayout(layout);
}

void MemoryParamWindow::_createCallibrationBox(){
    _callibrationBox = new QGroupBox(tr("Kalibrierung"));
    
    _callibrationLabel = new MemoryCallibrationLabel();
   

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(_callibrationLabel,0,0);// row column

    // layout->setColumnStretch(1, 10);

    _callibrationBox->setLayout(layout);
}

void MemoryParamWindow::setCallibrationImage(cv::Mat mat){
    QPixmap pix = QPixmap::fromImage(QImage((unsigned char*) mat.data, mat.cols, mat.rows, QImage::Format_RGB32));
    // QPixmap pix= QPixmap::fromImage(QImage(data, width, height, QImage::Format_RGB888).rgbSwapped());
    _callibrationLabel->setPixmap(pix);
}

void MemoryParamWindow::rowChanged(){
    std::cout << "ROW CHANGED : " << _rowComboBox->itemData(_rowComboBox->currentIndex(), IdRole).toInt() << "\n";
}

void MemoryParamWindow::colChanged(){
    std::cout << "ROW CHANGED : " << _rowComboBox->itemData(_rowComboBox->currentIndex(), IdRole).toInt() << "\n";
}

void MemoryParamWindow::handleMyCustomEvent(const KinectEvent *event){
    setCallibrationImage(event->getCustomData2());
}

// void MemoryParamWindow::mouseMoveEvent(QMouseEvent *e){
//     std::cout << "MemoryParamWindow :: mouseMoveEvent event XY : " << e->x() << ", " << e->y() << " \n";
// }

// void MemoryParamWindow::mouseReleaseEvent(QMouseEvent *e){
//     std::cout << "MemoryParamWindow :: mouseReleaseEvent event XY : " << e->x() << ", " << e->y() << " \n";
// }

// void MemoryParamWindow::mouseDoubleClickEvent(QMouseEvent *e){
//     std::cout << "MemoryParamWindow :: mouseDoubleClickEvent event XY : " << e->x() << ", " << e->y() << " \n";
// }

// void MemoryParamWindow::mousePressEvent(QMouseEvent *e){
//     std::cout << "MemoryParamWindow :: mousePressEvent event XY : " << e->x() << ", " << e->y() << " \n";
// }

// void MemoryParamWindow::keyPressEvent(QKeyEvent *event){
//     std::cout << "MemoryParamWindow :: KEY EVENT : \n";

// }



