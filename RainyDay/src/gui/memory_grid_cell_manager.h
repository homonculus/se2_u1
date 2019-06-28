
#ifndef MEMORYGRIDCELLMANAGER_H
#define MEMORYGRIDCELLMANAGER_H

#include <QPoint>
#include <vector>
#include <iostream>
#include <math.h>  
#include <opencv2/opencv.hpp>

enum MemoryGridCellType{MGC_TOP, MGC_BOTTOM, MGC_LEFT, MGC_RIGHT};

class MemoryGridCell{
    public:
        std::vector<QPoint> points;
        MemoryGridCellType type;
        float baseline;
        float average;
        float threshold_1;
        float threshold_2;
        int activity;
        MemoryGridCell(MemoryGridCellType _t, int _i){
            type = _t;
            idx = _i;
            baseline = 0;
            average = 0;
            threshold_1 = 0.5;
            threshold_2 = 0.8;
            activity = 0;
        }
        int idx;
        std::vector<QPoint> getPoint(){
            return points;
        }
        void addPoint(QPoint point){
            points.push_back(point);
        }
        void setActivity(){
            if (std::abs(baseline-average) > 300){
                activity = 1;
                std::cout << "IS GREATER THAN!!!!!! BASELINE - AVERAGE : " << baseline << " - " << average << " = " << std::abs(baseline-average) << "\n";
            }
            else{
                activity = 0;
                std::cout << "IS LESS THAN!!!!!!  BASELINE - AVERAGE : " << baseline << " - " << average << " = " << ( baseline-average) << "\n";
            }
        }
        void setBaseline(float val){ baseline = val;};
        QPoint getTopLeft(){ return points[0];};
        QPoint getTopRight(){return points[1];};
        QPoint getBottomLeft(){return points[2];};
        QPoint getBottomRight(){return points[3];};
};

class MemoryGridCellManager{
    public:
        std::vector<MemoryGridCell*> *gridcells;
        MemoryGridCellManager();
        std::vector<MemoryGridCell*> getGridCells(){ return *gridcells;};
        void createGridCells(int nrows, int ncols);
        void checkIfPointInGridCell(int x, int y, int size_w, int size_h, int size_margin);
        void setBaselines(cv::Mat *depth);
        void setAverageDepths(cv::Mat *depth);
};

#endif // MEMORYGRIDCELLMANAGER_H