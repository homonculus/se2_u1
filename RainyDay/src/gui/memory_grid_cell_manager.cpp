#include "memory_grid_cell_manager.h"

MemoryGridCellManager::MemoryGridCellManager(){
    gridcells = new std::vector<MemoryGridCell*>();
}

void MemoryGridCellManager::createGridCells(int nrows, int ncols){
    int margin = 100;
    int total_w = 512;
    int total_h = 424;
    int cell_h = round((total_h - 2*margin)/nrows);
    int cell_w = round((total_w - 2*margin)/ncols);

    if (gridcells->size() > 0){ gridcells->clear();}

    for (int r=0;r<nrows;r++){
        MemoryGridCell* cell_left = new MemoryGridCell(MGC_LEFT, r);
        MemoryGridCell* cell_right = new MemoryGridCell(MGC_RIGHT, r);
        int top = r*cell_h + margin;
        int bottom = top + cell_h;
        cell_left->addPoint(QPoint(0,top));
        cell_left->addPoint(QPoint(margin,top));
        cell_left->addPoint(QPoint(0,bottom));
        cell_left->addPoint(QPoint(margin,bottom));
        cell_right->addPoint(QPoint(total_w-margin,top));
        cell_right->addPoint(QPoint(total_w,top));
        cell_right->addPoint(QPoint(total_w-margin,bottom));
        cell_right->addPoint(QPoint(total_w,bottom));
        gridcells->push_back(cell_left);
        gridcells->push_back(cell_right);
    }

    for (int c=0;c<ncols;c++){
        MemoryGridCell* cell_top = new MemoryGridCell(MGC_TOP, c);
        MemoryGridCell* cell_bottom = new MemoryGridCell(MGC_BOTTOM, c);
        int left = c*cell_w + margin;
        int right = left + cell_w;
        cell_top->addPoint(QPoint(left,0));//top left
        cell_top->addPoint(QPoint(right,0));// top right
        cell_top->addPoint(QPoint(left,margin));//bottom left
        cell_top->addPoint(QPoint(right,margin));//bottom right
        cell_bottom->addPoint(QPoint(left,total_h-margin));//top left
        cell_bottom->addPoint(QPoint(right,total_h-margin));// top right
        cell_bottom->addPoint(QPoint(left,total_h));//bottom left
        cell_bottom->addPoint(QPoint(right,total_h));//bottom right
        gridcells->push_back(cell_top);
        gridcells->push_back(cell_bottom);
    }
}

void MemoryGridCellManager::checkIfPointInGridCell(int x, int y, int size_w, int size_h, int size_margin){
    // int _m = size_margin;
    // bool sides = (y > _m) && (y < (size_h - _m));
    // bool tb = (x > _m) && (x < (size_w - _m));
    // bool left = (x < _m) && sides;
    // bool right = (x > (size_w-_m)) && sides;
    // bool top = (y < _m) && tb;
    // bool bottom = (y > (size_h-_m)) && tb;

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

}

void MemoryGridCellManager::setBaselines(cv::Mat *depth){
	_calcAverageDepthForEachGridCell(depth);
	for (int i=0;i<gridcells->size();i++){
		(*gridcells)[i]->setBaseline((*gridcells)[i]->average);
	}
}

void MemoryGridCellManager::setActivities(cv::Mat *depth){
    _calcAverageDepthForEachGridCell(depth);
    _findIdxsMaxActivityForEachSide();
    _setSingleSelectionForEachSide();
}

void MemoryGridCellManager::_calcAverageDepthForEachGridCell(cv::Mat *depth){
	MemoryGridCell cell = *(*gridcells)[0];
	float n = (cell.getTopRight().x() - cell.getTopLeft().x() ) * (cell.getBottomLeft().y() - cell.getTopLeft().y());
	for (int i=0;i<gridcells->size();i++){
		for (int x=(*gridcells)[i]->getTopLeft().x();x<(*gridcells)[i]->getTopRight().x();x++){
			for (int y=(*gridcells)[i]->getTopLeft().y();y<(*gridcells)[i]->getBottomLeft().y();y++){
				(*gridcells)[i]->average += depth->at<float>(cv::Point(x,y));
			}
		}
		(*gridcells)[i]->average /= n;
		(*gridcells)[i]->setActivity();
	}

}

void MemoryGridCellManager::_findIdxsMaxActivityForEachSide(){
    // two parallel vectors corresponding to MGC_TOP, MGC_BOTTOM, MGC_LEFT, MGC_RIGHT
    // find cell with max value for that side and store it's idx in gridcells
    std::vector<float> maxs(4,0);
    std::vector<int> idxs_maxs(4,-1);
    for (int i=0;i<gridcells->size();i++){
        if ((*gridcells)[i]->activity != MGC_INACTIVE){
            int idx_type = (*gridcells)[i]->type;
            double val = (*gridcells)[i]->average;
            if (val > maxs[idx_type]){
                maxs[idx_type] = val;
                idxs_maxs[idx_type] = i;
            }
        }
    }
    _idxActivityBySide = idxs_maxs;
}

void MemoryGridCellManager::_setSingleSelectionForEachSide(){
    for (int i=0;i<_idxActivityBySide.size();i++){
        if (_idxActivityBySide[i] >= 0){
            (*gridcells)[_idxActivityBySide[i]]->setSelected();
        }
    }
}
