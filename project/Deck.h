#include <vector>
#include <iostream>
// #include "CardFactory.h"
#include "./card/Card.h"

class CardFactory;

class Deck : public std::vector<Card*> {
public:
	Deck() {};
	Deck(std::istream& in, const CardFactory* cf) {
		// TODO import deck from file
	};
	/*Top of the deck is at the end of the vector*/
	Card* draw() {
		Card* c = back();
		pop_back();
		return c;
	};
	friend std::istream& operator>>(std::istream& in, Deck& deck) {
		// TODO import deck from file
		return in;
	};
};

#pragma once
