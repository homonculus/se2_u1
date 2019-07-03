
#ifndef MEMORYGRIDCELLMANAGER_H
#define MEMORYGRIDCELLMANAGER_H

#include <QPoint>
#include <vector>
#include <iostream>
#include <math.h>  
#include <opencv2/opencv.hpp>

enum MemoryGridCellType{MGC_TOP, MGC_BOTTOM, MGC_LEFT, MGC_RIGHT};
enum MemoryGridCellActivity{MGC_INACTIVE, MGC_ACTIVE, MGC_SINGLESELECTION};

class MemoryGridCell{
    public:
        std::vector<QPoint> points;
        MemoryGridCellType type;
        float baseline;
        float average;
        float threshold_1;
        float threshold_2;
        MemoryGridCellActivity activity;
        MemoryGridCell(MemoryGridCellType _t, int _i){
            type = _t;
            idx = _i;
            baseline = 0;
            average = 0;
            threshold_1 = 0.5;
            threshold_2 = 0.8;
            activity = MGC_INACTIVE;
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
                activity = MGC_ACTIVE;
                std::cout << "IS GREATER THAN!!!!!! BASELINE - AVERAGE : " << baseline << " - " << average << " = " << std::abs(baseline-average) << "\n";
            }
            else{
                activity = MGC_INACTIVE;
                std::cout << "IS LESS THAN!!!!!!  BASELINE - AVERAGE : " << baseline << " - " << average << " = " << ( baseline-average) << "\n";
            }
        }

        void setSelected(){
            activity = MGC_SINGLESELECTION;

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
        void setActivities(cv::Mat *depth);

    private:
        void _calcAverageDepthForEachGridCell(cv::Mat *depth);
        std::vector<int> _findIdxsMaxActivityForEachSide();
        void _setSingleSelectionForEachSide(std::vector<int> idxMaxActivityBySide);
};

#endif // MEMORYGRIDCELLMANAGER_H