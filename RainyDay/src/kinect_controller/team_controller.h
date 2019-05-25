#ifndef TEAMCONTROLLER_H
#define TEAMCONTROLLER_H

class TeamController{
public:
	TeamController(int n_rows, int n_cols);
	void print_dimensions();
	int startDevice();
	int closeDevice();

private:
	int n_rows;
    int n_cols; 
    bool protonect_paused;
};

#endif // TEAMCONTROLLER
