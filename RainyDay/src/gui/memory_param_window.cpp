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

    _createDimensionsBox();
    _createCallibrationBox();
    _createControlBox();
    connect(_rowComboBox, SIGNAL(activated(int)), this, SLOT(rowChanged()));
    connect(_colComboBox, SIGNAL(activated(int)), this, SLOT(colChanged()));
    connect(_buttonStart, SIGNAL (released()),this, SLOT (handleStartButton()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(_dimensionsBox,0,0);// row column
    mainLayout->addWidget(_callibrationBox,1,0);
    mainLayout->addWidget(_buttonBox,2,0);
    this->setMouseTracking(true);

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
    QPixmap pix = QPixmap::fromImage(QImage((unsigned char*) mat.data, mat.cols, mat.rows, QImage::Format_RGB32));
    // QPixmap pix= QPixmap::fromImage(QImage(data, width, height, QImage::Format_RGB888).rgbSwapped());
    _callibrationLabel1->setPixmap(pix);


    cv::Mat h1 = findHomography(_convertQPointsToCVPoints(_callibrationLabel1->getHandlePoints()), _convertQPointsToCVPoints(_callibrationLabel2->getHandlePoints()));
    cv::Mat imout;
    cv::warpPerspective(mat, imout, h1, mat.size());

    QPixmap pix2 = QPixmap::fromImage(QImage((unsigned char*) imout.data, imout.cols, imout.rows, QImage::Format_RGB32));
    _callibrationLabel2->setPixmap(pix2);

    // Points in warped back to original space
    // cv::Mat h = findHomography(_convertQPointsToCVPoints(_callibrationLabel1->getHandlePoints()), _convertQPointsToCVPoints(_callibrationLabel2->getHandlePoints()));

    // cv::Mat imout_tooriginal;
    // cv::warpPerspective(imout, imout_tooriginal, h, mat.size());

    // cv::Mat matv = (cv::Mat_<double>(1,3) << 100,100,1);

    // cv::Mat math;
    // h1.convertTo(math,matv.type());

    // std::vector<QPoint*> ps = _callibrationLabel1->getHandlePoints();
    // cv::Mat m = math * matv.t();
    // std::cout << m << "\n";

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
    _drawGridInCallibrationLabel();
}

void MemoryParamWindow::colChanged(){
    std::cout << "ROW CHANGED : " << _rowComboBox->itemData(_rowComboBox->currentIndex(), IdRole).toInt() << "\n";
    _drawGridInCallibrationLabel();
}

void MemoryParamWindow::_drawGridInCallibrationLabel(){

    std::vector<std::vector<QPoint*> > gridpoints;
    std::cout << "MemoryParamWindow::_drawGridInCallibrationLabel \n";

    int nrows = _rowComboBox->itemData(_rowComboBox->currentIndex(), IdRole).toInt() +2;
    int ncols = _colComboBox->itemData(_colComboBox->currentIndex(), IdRole).toInt() +2;

    std::cout << "MemoryParamWindow::_drawGridInCallibrationLabel nrwos : " << nrows << "\n";
    std::cout << "MemoryParamWindow::_drawGridInCallibrationLabel nrwos : " << ncols << "\n";
    int margin = 100;
    int total_w = 512;
    int total_h = 424;
    int cell_h = round((total_h - 2*margin)/nrows);
    int cell_w = round((total_w - 2*margin)/ncols);
    // make left right grid


    std::cout << "MemoryParamWindow::_drawGridInCallibrationLabel 1\n";

    for (int r=0;r<nrows;r++){
    std::cout << "MemoryParamWindow::_drawGridInCallibrationLabel 2\n";
        std::vector<QPoint *> gpoints_left;
        std::vector<QPoint *> gpoints_right;
        int top = r*cell_h + margin;
        int bottom = top + cell_h;
        gpoints_left.push_back(new QPoint(0,top));
        gpoints_left.push_back(new QPoint(margin,top));
        gpoints_left.push_back(new QPoint(0,bottom));
        gpoints_left.push_back(new QPoint(margin,bottom));

        gpoints_right.push_back(new QPoint(total_w-margin,top));
        gpoints_right.push_back(new QPoint(total_w,top));
        gpoints_right.push_back(new QPoint(total_w-margin,bottom));
        gpoints_right.push_back(new QPoint(total_w,bottom));

        gridpoints.push_back(gpoints_left);
        gridpoints.push_back(gpoints_right);
    }
    std::cout << "MemoryParamWindow::_drawGridInCallibrationLabel 3\n";

    for (int c=0;c<ncols;c++){

        std::vector<QPoint *> gpoints_top;
        std::vector<QPoint *> gpoints_bottom;
        int left = c*cell_w + margin;
        int right = left + cell_w;
        std::cout << "MemoryParamWindow::_drawGridInCallibrationLabel 4 with c : " << left << "\n";

        gpoints_top.push_back(new QPoint(left,0));//top left
        gpoints_top.push_back(new QPoint(right,0));// top right
        gpoints_top.push_back(new QPoint(left,margin));//bottom left
        gpoints_top.push_back(new QPoint(right,margin));//bottom right

        gpoints_bottom.push_back(new QPoint(left,total_h-margin));//top left
        gpoints_bottom.push_back(new QPoint(right,total_h-margin));// top right
        gpoints_bottom.push_back(new QPoint(left,total_h));//bottom left
        gpoints_bottom.push_back(new QPoint(right,total_h));//bottom right
        gridpoints.push_back(gpoints_top);
        gridpoints.push_back(gpoints_bottom);
    }
    std::cout << "MemoryParamWindow::_drawGridInCallibrationLabel 5\n";

 
    _callibrationRenderArea2->setGridPoints(gridpoints);
}

void MemoryParamWindow::handleMyCustomEvent(const KinectEvent *event){
    setCallibrationImage(event->getCustomData2());
}

void MemoryParamWindow::updateMemoryCallibrationLabelRects(int idx){
    if (idx == 1){
        _callibrationRenderArea1->updatePoints(_callibrationLabel1->getHandlePoints());
    } else if (idx == 2){
        _callibrationRenderArea2->updatePoints(_callibrationLabel2->getHandlePoints());
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


