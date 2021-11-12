#include "CardFactory.h"
#include "./card/Card.h"
#include <iostream>
#include <list>
#include <string>

class TradeArea {
	std::list<Card*> cards;
public:
	TradeArea() {};
	TradeArea(std::istream&, const CardFactory*);
	TradeArea& operator+=(Card*);
	bool legal(Card*);
	Card* trade(std::string);
	int numCards();
	friend std::ostream& operator <<(std::ostream& os, const TradeArea& tradeArea);
};

TradeArea::TradeArea(std::istream& in, const CardFactory* cf) {
	// TODO implement
}

TradeArea& TradeArea::operator+=(Card* c) {
	cards.push_back(c);
	return *this;
}

bool TradeArea::legal(Card* card) {
	for (Card* c: cards) {
		if ((*c).getName() == (*card).getName()) {
			return true;
		}
	}
	return false;
}

Card* TradeArea::trade(std::string s) {
	Card* card = NULL;
	for(Card* c: cards) {
		if ((*c).getName() == s) {
			card = c;
			break;
		}
	}
	if (card == NULL) {
		// idk
	} else {
		cards.remove(card);
	}
	return card;
}

int TradeArea::numCards() {
	return cards.size();
}

std::ostream& operator <<(std::ostream& os, const TradeArea& tradeArea) {
	for(Card* c: tradeArea.cards) {
		os << *c << " ";
	}
	return os;
}

#pragma once
