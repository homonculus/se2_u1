#include "memory_model.h"
#include "csvreader.cpp"
#include "util.cpp"
#include <iostream>
#include <string>


void MemoryModel::readAllCardsFromFile(std::string path){
	std::ifstream file(path);
	CSVRow row;
	while(file >> row)
	{
		MemoryCard* c1 = _makeCard(row[0]);
		MemoryCard* c2 = _makeCard(row[1]);
		c1->linkedCards.push_back(c2);
		c2->linkedCards.push_back(c1);
		_all_cards.push_back(c1);
		_all_cards.push_back(c2);
	}
}

MemoryCard* MemoryModel::_makeCard(std::string s){
	MemoryCard* card = new MemoryCard();
	card->text = s;
	return card;
}

void MemoryModel::initGameCards(int num_cards){
	_clearGameCards();
	if (!testing){std::random_shuffle(std::begin(_all_cards), std::end(_all_cards));}
	_buildGameCardsWithRequiredNumberOfPairs(num_cards);
	if (!testing){std::random_shuffle(std::begin(_game_cards), std::end(_game_cards));}
}

void MemoryModel::initGameStats(){
	_gamestats.currentlySelectedCardsByTeam.reserve(2);
	_gamestats.currentlySelectedCardsByTeam[0] = -1;
	_gamestats.currentlySelectedCardsByTeam[1] = -1;

	_gamestats.idxsFoundByTeam[0] = {-1}

}

void MemoryModel::_clearGameCards(){
	if (_game_cards.size()>0){
		_game_cards.clear();
	}
}

void MemoryModel::_buildGameCardsWithRequiredNumberOfPairs(int num_cards){
	int i = 0;
	while(_game_cards.size()<num_cards && _game_cards.size()<_all_cards.size()){
		MemoryCard* currentCard = _all_cards[i];
		// Check if card already added to gamecards
		std::vector<MemoryCard*>::iterator it = std::find(_game_cards.begin(), _game_cards.end(), currentCard);
		if (it == _game_cards.end()){
			// add card selected
			_game_cards.push_back(currentCard);
			// Add all linked cards for card selected
			for (int j=0;j<currentCard->linkedCards.size();j++){
				_game_cards.push_back(currentCard->linkedCards[j]);
			}
		}
		i+=1;
	}
}

bool MemoryModel::validGameEvent(MemoryEvent e){
	// Card has already been sucessfully overturned
	if (testing) _logEvent(e);

	bool t1 = (std::find(_gamestats.idxsFoundByTeam[e.team].begin(), _gamestats.idxsFoundByTeam[e.team].end(),  e.idx_selected) != _gamestats.idxsFoundByTeam[e.team].end());//(_gamestats.idxsFoundByTeam[e.team], e.idx_selected);
	bool t2 = (_gamestats.currentlySelectedCardsByTeam[e.team] == e.idx_selected);

	std::cout << "MemoryModel::validGameEvent : previously selected :" << _gamestats.currentlySelectedCardsByTeam[e.team] << " now selected :" << e.idx_selected << std::endl;
	if (t1 || t2){ 
		if (testing) std::cout << "MemoryModel::validGameEvent : NOT valid move" << t1 << t2 << "\n";
		_gamestats.flag = GE_INVALID;
		return false; 
	}
	if (testing) std::cout << "MemoryModel::validGameEvent : is valid move\n";
	return true;
}

bool MemoryModel::isFirstMoveForTeam(MemoryEvent e){
	if (_gamestats.currentlySelectedCardsByTeam[_gamestats.currentTeam]>=0){
		if (testing) std::cout << "MemoryModel::isFirstMoveForTeam : NOT first move\n";
		return false;
	}
	if (testing) std::cout << "MemoryModel::isFirstMoveForTeam : is first move\n";
	_gamestats.flag = GE_ISFIRSTMOVE;
	return true;
}

void MemoryModel::saveSelection(MemoryEvent e){
	_gamestats.currentlySelectedCardsByTeam[e.team] = e.idx_selected;
}

bool MemoryModel::correctMatch(MemoryEvent e){
	MemoryCard* _selected_card = _game_cards[e.idx_selected];
	MemoryCard* _firstSelected = _firstCardSelected(e);
	if (testing) std::cout << "MemoryModel::correctMatch : idx selected(" << e.idx_selected << ") text(" << _selected_card->text << ") firstcard(" << _firstSelected->text << ")\n";
	if (_selected_card->linkedCards[0] == _firstCardSelected(e)){
		_gamestats.flag = GE_ISCORRECTMATCH;
		return true;
	}
	return false;
}

void MemoryModel::saveScore(MemoryEvent e){
	// _gamestats.idxsFoundByTeam[e.team].push_back(e.idx_selected);
	// _gamestats.idxsFoundByTeam[e.team].push_back(_gamestats.currentlySelectedCardsByTeam[e.team]);
	_gamestats.idxsFound.push_back(e.idx_selected);
	_gamestats.idxsFound.push_back(_gamestats.currentlySelectedCardsByTeam[e.team]);
}

void MemoryModel::moveToNextTeam(MemoryEvent e){
	_gamestats.currentTeam = !_gamestats.currentTeam;
}

void MemoryModel::cleanupCurrentSelections(MemoryEvent e){
	_gamestats.currentlySelectedCardsByTeam[e.team] = -1;
}

void MemoryModel::_printArrayOfCards(std::vector<MemoryCard*> cards){
	for (int i=0;i<cards.size();i++){
		std::cout << cards[i]->text<< "\n";
	}
}

void MemoryModel::printContent(){
	std::cout << "ALL CARDS : "<< "\n";
	_printArrayOfCards(_all_cards);
	std::cout << "GAME CARDS : "<< "\n";
	_printArrayOfCards(_game_cards);
}

void MemoryModel::_logEvent(MemoryEvent e){
	std::cout << "GAME EVENT : team(" << e.team << ") idx:(" << e.idx_selected << ")\n";
}

MemoryGameEventFlags MemoryModel::getGameStatusFlag(){
	if (testing) std::cout << "MemoryModel::getGameStatusFlag : status is " << _gamestats.flag << std::endl;
	return _gamestats.flag;
}


