#include <vector>
#include "CardFactory.h"
#include "./card/Card.h"

#include <iostream>

class DiscardPile: public std::vector<Card*> {
public:
	DiscardPile() {};
	DiscardPile(std::istream& in, const CardFactory* cf) {
		char chars[110], ca;
		in.getline(chars, 110);
		Card* card;
		for (int i = 13; i < in.gcount() - 1; i++) {
			ca = chars[i];
			card = ((CardFactory*)cf)->getCard(ca);
			push_back(card);
		}
	};
	DiscardPile& operator+=(Card* card) {
		push_back(card);
		return *this;
	}
	Card* pickUp() {
		Card* c = back();
		pop_back();
		return c;
	};
	Card* top() {
		if (empty()) return NULL;
		return back();
	}
	void print(std::ostream& os) {
		os << "DiscardPile: ";
		for (Card* c : *this) {
			os << *c << std::endl;
		}
	};
	friend std::ostream& operator <<(std::ostream& os, DiscardPile& discardPile) {
		os << "DiscardPile: ";
		if (!discardPile.empty()) {
			os << *(discardPile.top());
		}
		return os;
	};

	void writeToFile(std::ostream& os) {
		os << "DiscardPile: ";
		for (Card* c : *this) {
			os << *c;
		}
		os << "\n";
	}
};

#pragma once
