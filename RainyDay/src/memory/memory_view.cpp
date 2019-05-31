#include "memory_view.h"

void MemoryView::initGameView(MemoryInfo* info, GridInfo* dimensions){
	_ginfo = info;
	_dimensions = dimensions;
	_drawGrid();
}

void MemoryView::_drawGrid(){
	
}

void MemoryView::updateView(){

}

void MemoryView::highlightColumnForTeam(int idx, int team){

}

void MemoryView::highlightRowForTeam(int idx, int team){

}