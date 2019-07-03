#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include "memory_info.h"
#include "grid.h"

class MemoryView{
	public:
		void initGameView(MemoryInfo* info, GridInfo* dimensions);
		void updateView();
		void refreshCellSelections();
		void setSelectedColumn(int c);
		void setSelectedRow(int r);
		void update();
		Grid* getGrid() { return _grid; }
		
	private:
		MemoryInfo* _ginfo;
		GridInfo* _dimensions;
		void _drawGrid();
		void _makeGridCellInfos();
		std::vector<GridCell*> cellsInfo;
		Grid* _grid;
		int _selectedRow;
		int _selectedCol;
};

# endif// MEMORYVIEW_H