#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include "memory_info.h"
// #include "selectable_grid.h"
#include "render_window.h"

class MemoryView{
	public:
		void initGameView(MemoryInfo* info, GridInfo* dimensions);
		void updateView();
		void refreshCellSelections();
		void showWindow();
		void setSelectedColumn(int c);
		void setSelectedRow(int r);
		void setDelegate(RenderWindowDelegate* d);
		RenderWindow* getWindow(){ return _window; };
		
	private:
		MemoryInfo* _ginfo;
		GridInfo* _dimensions;
		void _drawGrid();
		void _makeGridCellInfos();
		std::vector<SelectableGridCell*> cellsInfo;
		RenderWindow* _window;
		SelectableGrid* _grid;
		int _selectedRow;
		int _selectedCol;
};

# endif// MEMORYVIEW_H