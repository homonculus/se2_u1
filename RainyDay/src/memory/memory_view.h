#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include "memory_info.h"
#include "selectable_grid.h"

class MemoryView{
	public:
		void initGameView(MemoryInfo* info, GridInfo* dimensions);
		void updateView();
		void highlightColumnForTeam(int idx, int team);
		void highlightRowForTeam(int idx, int team);

		
	private:
		MemoryInfo* _ginfo;
		GridInfo* _dimensions;
		void _drawGrid();
};

# endif// MEMORYVIEW_H