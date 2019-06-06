#include "memory_view.h"
// #include "render_window.h"
#include "selectable_grid.h"
#include <iostream>

#define COLOR_DEFAULT  std::string("#d1d8e0")
#define COLOR_SELECTED_SINGLE  std::string("#fc5c65")
#define COLOR_SELECTED_DOUBLE  std::string("#EA2027")

void MemoryView::initGameView(MemoryInfo* info, GridInfo* dimensions){
	_ginfo = info;
	_dimensions = dimensions;
	_drawGrid();
}

void MemoryView::_drawGrid(){
	_makeGridCellInfos();
	_window = new RenderWindow();
	_grid = new SelectableGrid(_dimensions->n_rows, _dimensions->n_cols);
	_grid->setCellsInfos(cellsInfo);
	_window->setRenderArea(_grid);
	_window->setTitle("hello");
}

void MemoryView::_makeGridCellInfos(){
	int i = 0;
	for (int r=0;r<_dimensions->n_rows;r++){
		for (int c=0;c<_dimensions->n_cols;c++){
			SelectableGridCell* cell = new SelectableGridCell();
			cell->color = COLOR_DEFAULT;
			cell->text = _ginfo->cards[i]->text;
			std::cout << "printing text " << cell->text << "\n";
			cellsInfo.push_back(cell);
			i++;
		}
	}
}

void MemoryView::updateView(){

}

void MemoryView::refreshCellSelections(){
	int i = 0;
	for (int r=0;r<_dimensions->n_rows;r++){
		for (int c=0;c<_dimensions->n_cols;c++){
			cellsInfo[i]->text = _ginfo->cards[i]->text;
			std::cout << "selected r " << _selectedRow << _selectedCol << "\n";
			if (c == _selectedCol && r == _selectedRow){
				cellsInfo[i]->color = COLOR_SELECTED_DOUBLE;
			}
			else if (c == _selectedCol || r == _selectedRow){
				cellsInfo[i]->color = COLOR_SELECTED_SINGLE;
			}
			else{
				cellsInfo[i]->color = COLOR_DEFAULT;
			}
			i++;
		}
	}
	_grid->update();
}


void MemoryView::setDelegate(RenderWindowDelegate* d){
	_window->delegate = d;
}


void MemoryView::showWindow(){
	_window->show();
}

void MemoryView::setSelectedRow(int r){
	_selectedRow = r;
}
void MemoryView::setSelectedColumn(int c){
	_selectedCol = c;
}
