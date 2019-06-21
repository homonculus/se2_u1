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
    connect(_buttonToggleDepth, SIGNAL(toggled(bool)), this, SLOT(_toggleDepthOnlyOrRegistered(bool)));


    QGridLayout *mainLayout = new QGridLayout;
    // mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(_dimensionsBox,0,0);// row column
    mainLayout->addWidget(_callibrationBox,1,0);
    mainLayout->addWidget(_buttonBox,0,1);
    this->setMouseTracking(true);

    setLayout(mainLayout);
    _depthOnly = true;
}

void MemoryParamWindow::handleStartButton(){
    std::cout << "START BUTTON PRESSED!\n";
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
    layout->addWidget(_colLabel,0,2,Qt::AlignRight);
    layout->addWidget(_colComboBox,0,3);
    layout->addWidget(_buttonToggleDepthLabel,1,1,Qt::AlignRight);// row column
    layout->addWidget(_buttonToggleDepth,1,0);
    layout->addWidget(_buttonStart,3,0);

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
    // int r = 10;
    float t1 = 4500/3;
    float t2 = (4500*2)/3;
    // int e_x = std::min(p_x + r, s.width);
    // int s_y = std::max(p_y - r, 0);
    // int e_y = std::min(p_y + r, s.height);
    // std::cout << *mat << "\n";
    cv::Vec3b color;
    // std::cout << "MemoryParamWindow :: _thresholdImage " << mat->type() << "\n";
    float val;
    // std::cout << *mat << "\n";
    std::vector<std::vector<QPoint*> > points = _callibrationRenderArea2->getGridPoints();


    cv::Mat img = cv::Mat(s.height, s.width, CV_8UC4);

    std::vector<bool> active;
    for (int x=0;x<s.width;x++){
        for (int y=0;y<s.height;y++){
            val = mat->at<float>(cv::Point(x,y));

            // // find if x,y is within a grid controller
            // int _m = 100;
            // bool sides = (y > _m) && (y < (s.height - _m));
            // bool tb = (x > _m) && (x < (s.width - _m));
            // bool left = (x < _m) && sides;
            // bool right = (x > (s.width-_m)) && sides;
            // bool top = (y < _m) && tb;
            // bool bottom = (y > (s.height-_m)) && tb;

            // int top_left = 0;
            // int top_right = 1;
            // int bottom_left = 2;
            // int bottom_right = 3;

            // if (left){
            //     for (int i = 0;i<points.size();i++){
            //         // now how are indexes saved?
            //         if ((y > points[i][top_left]->y()) && (y<points[i][bottom_left]->y())){

            //         }
            //     }

            // }
            // else if (right){

            // }
            // else if (top){

            // }
            // else if (bottom){

            // }
    

        
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
            img.at<cv::Vec3b>(cv::Point(x,y)) = color;

            // mat
            // color = mat->at<cv::Vec3b>(cv::Point(x,y));
            // print(color);
            // color[0] = 255;
            // color[1] = 255;
            // color[2] = 255;
            // mat.at<cv::Vec3b>(cv::Point(x,y)) = color;
        }
    }
    return img;
}


