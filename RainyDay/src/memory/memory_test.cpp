#include "memory_controller.h"
#include <iostream>
#define S  "*****************************************\n"

using namespace std;

MemoryController make3x3Game(){
	GridInfo dims = {3,3,9};
	MemoryController m = MemoryController();
	m.testing = true;
	m.setDimensions(dims);
	m.setContentPath("./content.csv");
	m.setupGame();
	return m;
}

void doGameMove(int team,int selection, MemoryController m){
	MemoryEvent e0 = {team,selection};
	m.cardSelected(e0);
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

bool testSinglePlayerAllCorrect(){
	cout << S << "TESTING : correct match\n";
	MemoryController m = make3x3Game();
	doGameMove(0,0,m);
	doGameMove(0,1,m);
	if (m.getGameStatusFlag() != GE_ISCORRECTMATCH){
		return false;
	}
	doGameMove(0,2,m);
	doGameMove(0,3,m);
	if (m.getGameStatusFlag() != GE_ISCORRECTMATCH){
		return false;
	}
	doGameMove(0,4,m);
	doGameMove(0,5,m);
	if (m.getGameStatusFlag() != GE_ISCORRECTMATCH){
		return false;
	}
	doGameMove(0,6,m);
	doGameMove(0,7,m);
	if (m.getGameStatusFlag() != GE_ISCORRECTMATCH){
		return false;
	}
	return true;
}

bool testOverIdx(){
	cout << S << "TESTING : idx selected over available n cards\n";
	MemoryController m = make3x3Game();
	doGameMove(0,8,m);
	if (m.getGameStatusFlag() != GE_INVALID){
		return false;
	}
	return true;
}

bool testMoveToNextTeam(){
	cout << S << "TESTING : saving score\n";
	MemoryController m = make3x3Game();
	MemoryInfo* ginfo = m.getGameInfo();
	// first team 0, make wrong match
	doGameMove(0,0,m);
	if (ginfo->currentTeam != 0){ return false; }
	doGameMove(0,2,m);
	if (ginfo->currentTeam != 1){ return false; }
	// now team 1s turn, make 1 correct match, then one wrong
	doGameMove(1,2,m);
	if (ginfo->currentTeam != 1){ return false; }
	doGameMove(1,3,m);
	if (ginfo->currentTeam != 1){ return false; }
	doGameMove(1,4,m);
	if (ginfo->currentTeam != 1){ return false; }
	doGameMove(1,6,m);
	if (ginfo->currentTeam != 0){ return false; }
	return true;
}

int main(){

	bool t1 = testIsValid_doubleSelection();
	bool t2 = testSinglePlayerAllCorrect();
	bool t3 = testOverIdx();
	bool t4 = testMoveToNextTeam();

	if (t1 && t2 && t3 && t4){
		cout << S << "ALL TESTS PASS\n";
	}
	else{
		cout << S << "TESTS FAILED\n";
	}
}