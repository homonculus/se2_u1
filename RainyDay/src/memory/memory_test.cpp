#include "memory_controller.h"
#include <iostream>
#define S  "*****************************************\n"

using namespace std;

MemoryController make3x3Game(){
	MemoryController m = MemoryController();
	m.testing = true;
	m.setDimensions(3,3);
	m.setContentPath("./content.csv");
	m.setupGame();
	return m;
}

void doGameMove(int team,int selection, MemoryController m){
	MemoryEvent e0 = {team,selection};
	m.gameEvent(e0);
}

bool testIsValid_doubleSelection(){
	cout << S << "TESTING : double selection in one turn\n";
	MemoryController m = make3x3Game();
	doGameMove(0,0,m);
	doGameMove(0,0,m);
	bool t1 = (m.getGameStatusFlag() == GE_INVALID);
	if (t1){
		return true;
	}
	return false;
}

bool testCorrectMatch(){
	cout << S << "TESTING : correct match\n";
	MemoryController m = make3x3Game();
	doGameMove(0,0,m);
	doGameMove(0,1,m);
	bool t1 = (m.getGameStatusFlag() == GE_ISCORRECTMATCH);
	cout << GE_ISCORRECTMATCH << " for GE_ISCORRECTMATCH "<< t1 << "\n"; 
	if (t1 == true){
		return true;
	}
	return false;
}

int main(){

	bool t1 = testIsValid_doubleSelection();
	bool t2 = testCorrectMatch();

	if (t1 && t2){
		cout << S << "ALL TESTS PASS\n";
	}
	else{
		cout << S << "TESTS FAILED\n";
	}
}