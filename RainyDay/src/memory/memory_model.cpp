#include "memory_model.h"
#include "csvreader.cpp"
#include "util.cpp"
#include <iostream>
#include <string>

#define NOCARDSELECTED -1;

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

void MemoryModel::initGameInfo(int num_cards){
	_ginfo.currentlySelectedCardsByTeam.reserve(2);
	_ginfo.currentlySelectedCardsByTeam[0] = NOCARDSELECTED;
	_ginfo.currentlySelectedCardsByTeam[1] = NOCARDSELECTED;
	vector<int> blank(5,99);
	_ginfo.idxsFoundByTeam.push_back(blank);
	_ginfo.idxsFoundByTeam.push_back(blank);
	_initGameCards(num_cards);
}

void MemoryModel::_initGameCards(int num_cards){
	_clearGameCards();
	if (!testing){std::random_shuffle(std::begin(_all_cards), std::end(_all_cards));}
	_buildGameCardsWithRequiredNumberOfPairs(num_cards);
	if (!testing){std::random_shuffle(std::begin(_ginfo.cards), std::end(_ginfo.cards));}
	_assignCardsTheirGameIdx();
}

void MemoryModel::_clearGameCards(){
	if (_ginfo.cards.size()>0){
		_ginfo.cards.clear();
	}
}

void MemoryModel::_buildGameCardsWithRequiredNumberOfPairs(int num_cards){
	int i = 0;
	while(_ginfo.cards.size()<(num_cards-1) && _ginfo.cards.size()<_all_cards.size()){
		MemoryCard* currentCard = _all_cards[i];
		// Check if card already added to gamecards
		std::vector<MemoryCard*>::iterator it = std::find(_ginfo.cards.begin(), _ginfo.cards.end(), currentCard);
		if (it == _ginfo.cards.end()){
			// add card selected
			_ginfo.cards.push_back(currentCard);
			// Add all linked cards for card selected
			for (int j=0;j<currentCard->linkedCards.size();j++){
				_ginfo.cards.push_back(currentCard->linkedCards[j]);
			}
		}
		i+=1;
	}
	if (testing) std::cout << "_buildGameCardsWithRequiredNumberOfPairs : " << _ginfo.cards.size() << " playing, for " << num_cards << " gamevields\n";
}

void MemoryModel::_assignCardsTheirGameIdx(){
	for (int i=0;i<_ginfo.cards.size();i++){
		_ginfo.cards[i]->idx = i;
	}
}

bool MemoryModel::validGameEvent(MemoryEvent e){
	if (testing) _logEvent(e);
	bool t1 = contains(_ginfo.idxsFound, e.idx_selected); // card has already been successfully matched/found
	bool t2 = (_ginfo.currentlySelectedCardsByTeam[e.team] == e.idx_selected); // card was just overturned (but not yet matched) ie double selected
	bool t3 = !(e.idx_selected < _ginfo.cards.size()); // is not a card, but empty grid field (ie odd number of cells in grid)
	std::cout << "MemoryModel::validGameEvent : previously selected :" << _ginfo.currentlySelectedCardsByTeam[e.team] << " now selected :" << e.idx_selected << std::endl;
	if (t1 || t2 || t3){ 
		if (testing) std::cout << "MemoryModel::validGameEvent : NOT valid move" << t1 << t2 << "\n";
		_ginfo.flag = GE_INVALID;
		return false; 
	}
	if (testing) std::cout << "MemoryModel::validGameEvent : is valid move\n";
	_incrementCardViewCount(e);
	return true;
}

void MemoryModel::_incrementCardViewCount(MemoryEvent e){
	_ginfo.cards[e.idx_selected]->viewCount += 1;
}

bool MemoryModel::isFirstMoveForTeam(MemoryEvent e){
	if (_ginfo.currentlySelectedCardsByTeam[_ginfo.currentTeam]>=0){
		if (testing) std::cout << "MemoryModel::isFirstMoveForTeam : NOT first move\n";
		return false;
	}
	if (testing) std::cout << "MemoryModel::isFirstMoveForTeam : is first move\n";
	_ginfo.flag = GE_ISFIRSTMOVE;
	return true;
}

void MemoryModel::saveSelection(MemoryEvent e){
	_ginfo.currentlySelectedCardsByTeam[e.team] = e.idx_selected;
}

bool MemoryModel::correctMatch(MemoryEvent e){
	MemoryCard* selected_card = _ginfo.cards[e.idx_selected];
	if (selected_card->linkedCards[0] == _firstCardSelected(e)){
		_ginfo.flag = GE_ISCORRECTMATCH;
		return true;
	}
	return false;
}

void MemoryModel::saveScore(MemoryEvent e){
	if (testing) std::cout << "MemoryModel::saveScore 0\n";
	_ginfo.idxsFoundByTeam[e.team].push_back(e.idx_selected);
	_ginfo.idxsFoundByTeam[e.team].push_back(_ginfo.currentlySelectedCardsByTeam[e.team]);
	_ginfo.idxsFound.push_back(e.idx_selected);
	_ginfo.idxsFound.push_back(_ginfo.currentlySelectedCardsByTeam[e.team]);
	MemoryCard* selected_card = _ginfo.cards[e.idx_selected];
	MemoryCard* first_selected = _firstCardSelected(e);
	selected_card->status = e.team + 1;
	first_selected->status = e.team + 1;
	if (testing) std::cout << "MemoryModel::saveScore : idx selected(" << e.idx_selected << ") text(" << selected_card->text << ") firstcard(" << first_selected->text << ")\n";

}

void MemoryModel::moveToNextTeam(MemoryEvent e){
	_ginfo.currentTeam = !_ginfo.currentTeam;
	if (testing) std::cout << "MemoryModel::moveToNextTeam : team now(" << _ginfo.currentTeam << ")\n";
}

void MemoryModel::cleanupCurrentSelections(MemoryEvent e){
	_ginfo.currentlySelectedCardsByTeam[e.team] = NOCARDSELECTED;
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
	_printArrayOfCards(_ginfo.cards);
}

void MemoryModel::_logEvent(MemoryEvent e){
	std::cout << "GAME EVENT : team(" << e.team << ") idx:(" << e.idx_selected << ")\n";
}

MemoryGameEventFlags MemoryModel::getGameStatusFlag(){
	if (testing) std::cout << "MemoryModel::getGameStatusFlag : status is " << _ginfo.flag << std::endl;
	return _ginfo.flag;
}




