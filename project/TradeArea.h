#include "CardFactory.h"
#include "./card/Card.h"
#include <iostream>
#include <list>
#include <string>

class TradeArea {
public:
	std::list<Card*> cards;

	TradeArea() {};
	TradeArea(std::istream& in, const CardFactory* cf) {
		// TODO implement
	}
	TradeArea& operator+=(Card* c) {
		cards.push_back(c);
		return *this;
	};
	bool legal(Card* card) {
		for (Card* c : cards) {
			if ((*c).getName() == (*card).getName()) {
				return true;
			}
		}
		return false;
	}
	Card* trade(std::string s) {
		Card* card = NULL;
		for (Card* c : cards) {
			if ((*c).getName() == s) {
				card = c;
				break;
			}
		}
		if (card == NULL) {
			// idk
		}
		else {
			cards.remove(card);
		}
		return card;
	}
	int numCards() {
		return cards.size();
	};
	friend std::ostream& operator <<(std::ostream& os, const TradeArea& tradeArea) {
		for (Card* c : tradeArea.cards) {
			os << *c << " ";
		}
		return os;
	};
};

#pragma once
