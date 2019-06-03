#include "memory_view.h"
// #include "render_window.h"
#include "selectable_grid.h"
#include <iostream>

void MemoryView::initGameView(MemoryInfo* info, GridInfo* dimensions){
	_ginfo = info;
	_dimensions = dimensions;
	_drawGrid();

}

void MemoryView::_drawGrid(){
	std::vector<SelectableGridCell*> cells;
	for (int r=0;r<_dimensions->n_rows;r++){
		for (int c=0;c<_dimensions->n_cols;c++){
			SelectableGridCell cell = SelectableGridCell();
			cell.color = std::string("#a55eea");
			cells.push_back(&cell);
		}
	}
	_window = new RenderWindow();
	_grid = new SelectableGrid(_dimensions->n_rows, _dimensions->n_cols);
	_grid->setCellsInfos(cells);
	_window->setRenderArea(_grid);
	_window->setTitle("hello");
}

void MemoryView::updateView(){

}

void MemoryView::highlightColumnForTeam(int idx, int team){

}

void MemoryView::highlightRowForTeam(int idx, int team){

}


void MemoryView::showWindow(){
	_window->show();
}