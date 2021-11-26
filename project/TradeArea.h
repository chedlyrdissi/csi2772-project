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
		std::cout << "reading trade area\n";
		char chars[110], ca;
		in.getline(chars, 110);
		Card* card;
		for (int i = 11; i < in.gcount() - 1; i++) {
			ca = chars[i];
			card = ((CardFactory*)cf)->getCard(ca);
			cards.push_back(card);
		}
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

	/*
	Card* operator[](int i) {
		assert(i >= 0 && i < cards.size());
		return cards[i];
	}
	*/

	std::list<Card*>& getList() {
		return cards;
	}

	Card* trade(std::string s) {
		Card* card = NULL;
		for (Card* c : cards) {
			if ((*c).getName() == s) {
				card = c;
				break;
			}
		}
		if (card != NULL) {
			cards.remove(card);
		}
		return card;
	}

	int numCards() {
		return cards.size();
	};

	friend std::ostream& operator <<(std::ostream& os, const TradeArea& tradeArea) {
		os << "TradeArea: ";
		for (Card* c : tradeArea.cards) {
			os << *c << " ";
		}
		return os;
	};

	void writeToFile(std::ostream& os) {
		os << "TradeArea: ";
		for (Card* c : cards) {
			os << *c;
		}
		os << "\n";
	}
};

#pragma once
