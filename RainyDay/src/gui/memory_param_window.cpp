#include "memory_param_window.h"
#include <iostream>
#include <QtWidgets>
#include <algorithm>
#include <vector>

const int IdRole = Qt::UserRole;

MemoryParamWindow::MemoryParamWindow()
{
    setWindowTitle(tr("Memory Parameters"));

    _createDimensionsBox();
    _createCallibrationBox();
    _createControlBox();
    connect(_rowComboBox, SIGNAL(activated(int)), this, SLOT(rowChanged()));
    connect(_colComboBox, SIGNAL(activated(int)), this, SLOT(colChanged()));
    connect(_buttonStart, SIGNAL (released()),this, SLOT (handleStartButton()));
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
    mainLayout->addWidget(_buttonBox,2,0);
    this->setMouseTracking(true);
    // mainLayout->addWidget(_colLabel,1,0,Qt::AlignRight);
    // mainLayout->addWidget(_colComboBox,1,1);

    setLayout(mainLayout);
}

void MemoryParamWindow::handleStartButton(){
    std::cout << "START BUTTON PRESSED!\n";
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
    _callibrationLabel->createPoints();

    _callibrationRenderArea = new MemoryCallibrationRenderArea();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(_callibrationLabel,0,0);// row column
    layout->addWidget(_callibrationRenderArea,0,0);// row column

    // layout->setColumnStretch(1, 10);

    _callibrationBox->setLayout(layout);
}

void MemoryParamWindow::_createControlBox(){
    _buttonBox = new QGroupBox(tr("Kontrolle"));
    _buttonStart = new QPushButton("&Start", this);
    _buttonStop = new QPushButton("&Stop", this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(_buttonStart,0,0);// row column
    layout->addWidget(_buttonStop,0,1);
    // layout->setColumnStretch(1, 10);
    _buttonBox->setLayout(layout);
}


void MemoryParamWindow::setCallibrationImage(cv::Mat mat){
    _drawCallibrationPointsIn(mat);
    std::cout << mat.size() << "IMAGE SIZE \n";
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

void MemoryParamWindow::_drawCallibrationPointsIn(cv::Mat mat){
    std::vector<CallibrationPoint*> points = *_callibrationLabel->getPoints();
    std::cout << points.size() << "MemoryParamWindow::_drawCallibrationPointsI : points size\n";

    for (int i=0;i<points.size();i++){
        CallibrationPoint* p = points[i];
        _drawPointInMat(p->center.x, p->center.y, mat);
    }

}

void MemoryParamWindow::_drawPointInMat(int p_x, int p_y, cv::Mat mat){
    cv::Size s = mat.size();
    int r = 10;
    int s_x = std::max(p_x - r, 0);
    int e_x = std::min(p_x + r, s.width);
    int s_y = std::max(p_y - r, 0);
    int e_y = std::min(p_y + r, s.height);

    cv::Vec3b color;
    for (int x=s_x;x<e_x;x++){
        for (int y=s_y;y<e_y;y++){
            color = mat.at<cv::Vec3b>(cv::Point(x,y));
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            mat.at<cv::Vec3b>(cv::Point(x,y)) = color;
        }
    }
}


