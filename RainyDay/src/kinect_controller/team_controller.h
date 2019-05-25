#ifndef TEAMCONTROLLER_H
#define TEAMCONTROLLER_H


enum TeamControllerEventFlag{TC_COLUMNSELECTED, TC_ROWSELECTED, TC_CELLSELECTED};

struct TeamControllerEventInfo{
	TeamControllerEventFlag type;
	int selected;
};

class TeamController{
public:
	TeamController(int n_rows, int n_cols);
	bool start();
	bool end();

private:
	int n_rows;
    int n_cols; 
    bool protonect_paused;
};

#endif // TEAMCONTROLLER
