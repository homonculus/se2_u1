
#ifndef MEMORYGRIDCELL_H
#define MEMORYGRIDCELL_H

#include <QPoint>
#include <vector>
#include <iostream>
#include <math.h>  

enum MemoryGridCellType{MGC_TOP, MGC_BOTTOM, MGC_LEFT, MGC_RIGHT};
class MemoryGridCell{
    public:
        std::vector<QPoint> points;
        MemoryGridCellType type;
        MemoryGridCell(MemoryGridCellType _t, int _i){
            type = _t;
            idx = _i;
        }
        int idx;
        const QPoint * getAsQpoints(){
            QPoint pointsarray[4] = {
                points[0],
                points[2],
                points[3],
                points[1],
            };
            return pointsarray;
        }
        void addPoint(QPoint point){
            points.push_back(point);
        }
};

class MemoryGridCellManager{
    public:
        std::vector<MemoryGridCell> *gridcells;
        MemoryGridCellManager();
        std::vector<MemoryGridCell> getGridCells(){ return *gridcells;};
        void createGridCells(int nrows, int ncols){
            std::cout << "MemoryGridCellManager::createGridCell nrwos : " << nrows << "\n";
            std::cout << "MemoryGridCellManager::createGridCell nrwos : " << ncols << "\n";

            int margin = 100;
            int total_w = 512;
            int total_h = 424;
            int cell_h = round((total_h - 2*margin)/nrows);
            int cell_w = round((total_w - 2*margin)/ncols);
            // make left right grid

            std::cout << "MemoryGridCellManager::createGridCell 1\n";
            std::cout << gridcells << "\n";

            std::cout << gridcells->size() << " \n";
            if (gridcells->size() > 0){
                std::cout << "MemoryGridCellManager::createGridCell inside clear\n";

                gridcells->clear();
            }
            
            for (int r=0;r<nrows;r++){
                std::cout << "MemoryGridCellManager::createGridCell 2\n";
                MemoryGridCell cell_left = MemoryGridCell(MGC_LEFT, r);
                MemoryGridCell cell_right = MemoryGridCell(MGC_RIGHT, r);

                int top = r*cell_h + margin;
                int bottom = top + cell_h;
                cell_left.addPoint(QPoint(0,top));
                cell_left.addPoint(QPoint(margin,top));
                cell_left.addPoint(QPoint(0,bottom));
                cell_left.addPoint(QPoint(margin,bottom));

                cell_right.addPoint(QPoint(total_w-margin,top));
                cell_right.addPoint(QPoint(total_w,top));
                cell_right.addPoint(QPoint(total_w-margin,bottom));
                cell_right.addPoint(QPoint(total_w,bottom));

                gridcells->push_back(cell_left);
                gridcells->push_back(cell_right);
            }
            std::cout << "MemoryGridCellManager::createGridCell 3\n";

            for (int c=0;c<ncols;c++){

                MemoryGridCell cell_top = MemoryGridCell(MGC_TOP, c);
                MemoryGridCell cell_bottom = MemoryGridCell(MGC_BOTTOM, c);
                int left = c*cell_w + margin;
                int right = left + cell_w;
                std::cout << "MemoryGridCellManager::createGridCell 4 with c : " << left << "\n";

                cell_top.addPoint(QPoint(left,0));//top left
                cell_top.addPoint(QPoint(right,0));// top right
                cell_top.addPoint(QPoint(left,margin));//bottom left
                cell_top.addPoint(QPoint(right,margin));//bottom right

                cell_bottom.addPoint(QPoint(left,total_h-margin));//top left
                cell_bottom.addPoint(QPoint(right,total_h-margin));// top right
                cell_bottom.addPoint(QPoint(left,total_h));//bottom left
                cell_bottom.addPoint(QPoint(right,total_h));//bottom right
                gridcells->push_back(cell_top);
                gridcells->push_back(cell_bottom);
            }
            std::cout << "MemoryGridCellManager::createGridCell 5\n";
        };

        void checkIfPointInGridCell(int x, int y);
};

#endif // MEMORYGRIDCELL_H