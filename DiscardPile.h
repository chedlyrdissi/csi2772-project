#include <vector>
#include "CardFactory.h"
#include "./card/Card.h"

class DiscardPile: public std::vector<Card*> {
public:
	DiscardPile(istream&, const CardFactory*);
	DiscardPile& operator+=(Card*);
	Card* pickUp();
	Card* top();
	void print(std::ostream&);
	friend std::istream& operator>>(std::istream&, DiscardPile&);
}


DiscardPile(std::istream& in, const CardFactory* cf) {
	// TODO implement 
}

DiscardPile& operator+=(Card* card) {
	push_back(card);
	return *this;
}

Card* pickUp() {
	Card* c = back();
	pop_back();
	return c;
}

Card* top() {
	return back();
}

void print(std::ostream& os) {
	os << "DiscardPile" << endl;
	for(int i=0; i<size(); i++) {
		os << *((*this)[i]) << std::endl;
	}
}

std::istream& operator>>(std::istream& in, DiscardPile& discardPile) {
	// TODO implement
	return in;
}

#pragma once
