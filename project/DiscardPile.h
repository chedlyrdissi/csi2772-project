#include <vector>
#include "CardFactory.h"
#include "./card/Card.h"

class DiscardPile: public std::vector<Card*> {
public:
	DiscardPile() {};
	DiscardPile(std::istream&, const CardFactory*) {
		// TODO implement 
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
		return back();
	}
	void print(std::ostream& os) {
		os << "DiscardPile: ";
		for (Card* c : *this) {
			os << *c << std::endl;
		}
	};
	friend std::ostream& operator <<(std::ostream& os, DiscardPile& discardPile) {
		os << "DiscardPile " << discardPile.top();
		return os;
	};
};

#pragma once
