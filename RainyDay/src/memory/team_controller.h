// #ifndef TeamController_H
// #define TeamController_H

// #include "game.h"
// #include "memory_param_window.h"
// #include <vector>


// enum TeamControllerEventFlag{TC_COLUMNSELECTED, TC_ROWSELECTED, TC_CELLSELECTED};

// struct TeamControllerEventInfo{
// 	TeamControllerEventFlag type;
// 	int selected;
// 	int team;
// };

// class TeamControllerDelegate{
// 	public:
// 		virtual void teamControllerDidChange(TeamControllerEventInfo e) = 0;
// };


// class TeamController: public MemoryParamWindowDelegate{
// 	public:
// 		TeamController(GridInfo* dimensions);
// 		TeamControllerDelegate* delegate;
// 		void start();
// 		void MemoryParamWindowDidChange(int e);

// 	private:
// 		GridInfo* _dimensions;
// };

// # endif// TeamController_H