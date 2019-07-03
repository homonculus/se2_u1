#include "memory_param_window.h"
#include <iostream>
#include <QtWidgets>
#include <algorithm>
#include <vector>
#include <math.h>  
const int IdRole = Qt::UserRole;

MemoryParamWindow::MemoryParamWindow()
{
    setWindowTitle(tr("Memory Parameters"));

    std::cout << "MemoryParamWindow :: CREATING MEMORY GRID CELL MANAGER\n";
    _gridCellManager = new MemoryGridCellManager;
    _createDimensionsBox();
    _createCallibrationBox();
    _createControlBox();
    connect(_rowComboBox, SIGNAL(activated(int)), this, SLOT(rowChanged()));
    connect(_colComboBox, SIGNAL(activated(int)), this, SLOT(colChanged()));
    connect(_buttonStart, SIGNAL (released()),this, SLOT (handleStartButton()));
    connect(_buttonToggleDepth, SIGNAL(toggled(bool)), this, SLOT(_toggleDepthOnlyOrRegistered(bool)));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(1, 0);
    mainLayout->setColumnStretch(1, 2);
    mainLayout->setColumnStretch(1, 3);

    mainLayout->addWidget(_dimensionsBox,0,0);// row column
    mainLayout->addWidget(_callibrationBox,1,0);
    mainLayout->addWidget(_buttonBox,0,1);
    this->setMouseTracking(true);

    setLayout(mainLayout);
    _depthOnly = true;
    _setBaselines = false;
}

void MemoryParamWindow::handleStartButton(){
    std::cout << "START BUTTON PRESSED!\n";
    _setBaselines = true;

}

void MemoryParamWindow::_toggleDepthOnlyOrRegistered(bool on){
    _depthOnly = !on;
    std::cout << "MemoryParamWindow::_toggleDepthOnlyOrRegistered : " << on << "\n";

}

void MemoryParamWindow::_createDimensionsBox(){
    _dimensionsBox = new QGroupBox(tr("Spiel Dimensionen"));
    
    // row combo box
    _rowComboBox = new QComboBox;
    _rowComboBox->addItem(tr("2"),0);
    _rowComboBox->addItem(tr("3"),1);
    _rowComboBox->addItem(tr("4"),2);
    _rowComboBox->addItem(tr("5"),3);
    _rowLabel = new QLabel(tr("&Anzahl Reien:"));
    _rowLabel->setBuddy(_rowComboBox);

    // column combo box
    _colComboBox = new QComboBox;
    _colComboBox->addItem(tr("2"),0);
    _colComboBox->addItem(tr("3"),1);
    _colComboBox->addItem(tr("4"),2);
    _colComboBox->addItem(tr("5"),3);
    _colLabel = new QLabel(tr("&Anzahl Spalten:"));
    _colLabel->setBuddy(_colComboBox);

    // Registered image/depth toggle
    _buttonToggleDepth = new QRadioButton;
    _buttonToggleDepthLabel = new QLabel(tr("&Tiefe + RGB Zeigen"));
    _buttonToggleDepthLabel->setBuddy(_buttonToggleDepth);


    _buttonStart = new QPushButton("&Start", this);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(_rowLabel,0,0,Qt::AlignRight);// row column
    layout->addWidget(_rowComboBox,0,1);
    layout->addWidget(_colLabel,1,0,Qt::AlignRight);
    layout->addWidget(_colComboBox,1,1);
    layout->addWidget(_buttonToggleDepthLabel,0,3,Qt::AlignLeft);// row column
    layout->addWidget(_buttonToggleDepth,0,2,Qt::AlignRight);
    layout->addWidget(_buttonStart,1,3);

    _dimensionsBox->setLayout(layout);
}

void MemoryParamWindow::_createCallibrationBox(){
    _callibrationBox = new QGroupBox(tr("Kalibrierung"));
    _callibrationBox2 = new QGroupBox(tr("Resultat"));

    
    _callibrationLabel1 = new MemoryCallibrationLabel();
    _callibrationLabel1->idx = 1;
    _callibrationLabel1->createPoints();
    _callibrationLabel1->delegate = this;


    _callibrationLabel2 = new MemoryCallibrationLabel();
    _callibrationLabel2->idx = 2;
    _callibrationLabel2->createPoints();
    _callibrationLabel2->delegate = this;


    _callibrationRenderArea1 = new MemoryCallibrationRenderArea();
    updateMemoryCallibrationLabelRects(1);

    _callibrationRenderArea2 = new MemoryCallibrationRenderArea();
    updateMemoryCallibrationLabelRects(2);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(_callibrationLabel1,0,0);// row column
    layout->addWidget(_callibrationRenderArea1,0,0);// row column
    layout->addWidget(_callibrationLabel2,0,1);// row column
    layout->addWidget(_callibrationRenderArea2,0,1);// row column

    // layout->setColumnStretch(1, 10);

    _callibrationBox->setLayout(layout);
    _createGridCells();
    _drawGridInCallibrationLabel();
}

void MemoryParamWindow::_createControlBox(){
    // _buttonBox = new QGroupBox(tr("Kontrolle"));
    // _buttonStart = new QPushButton("&Start", this);
    // _buttonStop = new QPushButton("&Stop", this);

    // QGridLayout *layout = new QGridLayout;
    // layout->addWidget(_buttonStart,0,0);// row column
    // layout->addWidget(_buttonStop,0,1);
    // // layout->setColumnStretch(1, 10);
    // _buttonBox->setLayout(layout);
}

void MemoryParamWindow::_createGridCells(){
    int nrows = _rowComboBox->itemData(_rowComboBox->currentIndex(), IdRole).toInt() +2;
    int ncols = _colComboBox->itemData(_colComboBox->currentIndex(), IdRole).toInt() +2;
    _gridCellManager->createGridCells(nrows, nrows);

}


void MemoryParamWindow::setCallibrationImage(cv::Mat registered, cv::Mat depth){
    QPixmap pix = QPixmap::fromImage(QImage((unsigned char*) registered.data, registered.cols, registered.rows, QImage::Format_RGB32));
    _callibrationLabel1->setPixmap(pix);
    cv::Mat h = findHomography(_convertQPointsToCVPoints(_callibrationLabel1->getHandlePoints()), _convertQPointsToCVPoints(_callibrationLabel2->getHandlePoints()));
    int x = 2;
    if (_depthOnly){
        cv::Mat warped_dep;
        cv::warpPerspective(depth, warped_dep, h, depth.size());

        cv::Mat img = _thresholdImage(&warped_dep);
        QPixmap pix2 = QPixmap::fromImage(QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB32));
        _callibrationLabel2->setPixmap(pix2);
    }
    else{
        cv::Mat warped_reg;
        cv::warpPerspective(registered, warped_reg, h, registered.size());
        QPixmap pix2 = QPixmap::fromImage(QImage((unsigned char*) warped_reg.data, warped_reg.cols, warped_reg.rows, QImage::Format_RGB32));
        _callibrationLabel2->setPixmap(pix2);
    }


    if (_setBaselines){
        _gridCellManager->setBaselines(&depth);
        _setBaselines = false;
    }
    else{
        _gridCellManager->setActivities(&depth);
        _drawGridInCallibrationLabel();
    }
}

std::vector<cv::Point2f> MemoryParamWindow::_convertQPointsToCVPoints(std::vector<QPoint*> p){
    std::vector<cv::Point2f> cvps;
    for (int i=0;i<p.size();i++){
        cvps.push_back(cv::Point2f(p[i]->x(), p[i]->y()));
    }
    return cvps;
}
void MemoryParamWindow::rowChanged(){
    std::cout << "ROW CHANGED : " << _rowComboBox->itemData(_rowComboBox->currentIndex(), IdRole).toInt() << "\n";
    _createGridCells();
    _drawGridInCallibrationLabel();
}

void MemoryParamWindow::colChanged(){
    std::cout << "ROW CHANGED : " << _rowComboBox->itemData(_rowComboBox->currentIndex(), IdRole).toInt() << "\n";
    _createGridCells();
    _drawGridInCallibrationLabel();
}

void MemoryParamWindow::_drawGridInCallibrationLabel(){
    int nrows = _rowComboBox->itemData(_rowComboBox->currentIndex(), IdRole).toInt() +2;
    int ncols = _colComboBox->itemData(_colComboBox->currentIndex(), IdRole).toInt() +2;
    std::cout << "MemoryParamWindow::_drawGridInCallibrationLabel 5\n";
    _callibrationRenderArea2->setGridCells(_gridCellManager->getGridCells());
    std::cout << "MemoryParamWindow::_drawGridInCallibrationLabel 6\n";
}

void MemoryParamWindow::handleMyCustomEvent(const KinectEvent *event){
    setCallibrationImage(event->getCustomData2(), event->getCustomData1());
}

void MemoryParamWindow::updateMemoryCallibrationLabelRects(int idx){
    if (idx == 1){
        _callibrationRenderArea1->updatePoints(_callibrationLabel1->getHandlePoints());
    } else if (idx == 2){
        _callibrationRenderArea2->updatePoints(_callibrationLabel2->getHandlePoints());
    }
}

cv::Mat MemoryParamWindow::_thresholdImage(cv::Mat *mat){
    cv::Size s = mat->size();
    float t1 = 4500/3;
    float t2 = (4500*2)/3;
    cv::Vec4b color;
    color[3] = 255;
    float val;
    // std::vector<std::vector<QPoint*> > points = _callibrationRenderArea2->getGridPoints();
    cv::Mat img = cv::Mat(s.height, s.width, CV_8UC4);
    std::vector<bool> active;
    for (int x=0;x<s.width;x++){
        for (int y=0;y<s.height;y++){
            val = mat->at<float>(cv::Point(x,y));
            if (val < t1){
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
            }
            else if (val >= t1 && val < t2){
                color[0] = 100;
                color[1] = 100;
                color[2] = 0;
            }
            else{
                color[0] = 100;
                color[1] = 100;
                color[2] = 100;
            }
            img.at<cv::Vec4b>(cv::Point(x,y)) = color;
        }
    }
    return img;
}


