#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include "memory_info.h"

class MemoryView{
	public:
		void initGameView(MemoryInfo* info, GridInfo dimensions);
		void updateView();
		
	private:
		MemoryInfo* _ginfo;
		GridInfo _dimensions;
		void _drawGrid();
};

# endif// MEMORYVIEW_H