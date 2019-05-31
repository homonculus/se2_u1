#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include "memory_info.h"
// #include "selectable_grid.h"
#include "render_window.h"

class MemoryView{
	public:
		void initGameView(MemoryInfo* info, GridInfo* dimensions);
		void updateView();
		void highlightColumnForTeam(int idx, int team);
		void highlightRowForTeam(int idx, int team);
		void showWindow();

		
	private:
		MemoryInfo* _ginfo;
		GridInfo* _dimensions;
		void _drawGrid();

		RenderWindow* _window;
		SelectableGrid* _grid;
};

# endif// MEMORYVIEW_H