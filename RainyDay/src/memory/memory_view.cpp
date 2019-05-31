#include "memory_view.h"
// #include "render_window.h"

#include <iostream>

void MemoryView::initGameView(MemoryInfo* info, GridInfo* dimensions){
	_ginfo = info;
	_dimensions = dimensions;
	_drawGrid();

}

void MemoryView::_drawGrid(){
	_window = new RenderWindow();
	// std::cout << "FINISHE DMAING WINDOW\n";
	_grid = new SelectableGrid();
	_window->setRenderArea(_grid);
	// _window->setTitle("hello");
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