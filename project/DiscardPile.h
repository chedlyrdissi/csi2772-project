#include <vector>
#include "CardFactory.h"
#include "./card/Card.h"

class DiscardPile: public std::vector<Card*> {
public:
	DiscardPile() {};
	DiscardPile(std::istream&, const CardFactory*);
	DiscardPile& operator+=(Card*);
	Card* pickUp();
	Card* top();
	void print(std::ostream&);
	friend std::istream& operator>>(std::istream&, DiscardPile&);
};


DiscardPile::DiscardPile(std::istream& in, const CardFactory* cf) {
	// TODO implement 
}

DiscardPile& DiscardPile::operator+=(Card* card) {
	push_back(card);
	return *this;
}

Card* DiscardPile::pickUp() {
	Card* c = back();
	pop_back();
	return c;
}

Card* DiscardPile::top() {
	return back();
}

void DiscardPile::print(std::ostream& os) {
	os << "DiscardPile" << std::endl;
	for (Card* c : *this) {
		os << *c << std::endl;
	}
}

std::istream& operator>>(std::istream& in, DiscardPile& discardPile) {
	// TODO implement
	return in;
}

#pragma once
