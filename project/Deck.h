#include <vector>
// #include "CardFactory.h"
#include "./card/Card.h"

class Deck : public std::vector<Card*> {
public:
	Deck() {};
	Deck(std::istream&, const CardFactory*) {};
	Card* draw();
	friend std::istream& operator>>(std::istream&, Deck&);
};

/*
Deck::Deck(std::istream& in, const CardFactory* cf) {
	// TODO import deck from file
}
*/

/*Top of the deck is at the end of the vector*/
Card* Deck::draw() {
	Card* c = back();
	pop_back();
	return c;
}

std::istream& operator>>(std::istream& in, Deck& d) {
	// TODO import deck from file
	return in;
}

#pragma once
