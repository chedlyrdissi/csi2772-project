#include <vector>
#include <iostream>
#include "./card/Card.h"
#include <fstream>

class CardFactory;

// #include "CardFactory.h"

class Deck : public std::vector<Card*> {
public:
	Deck() {};
	Deck(std::istream& in, const CardFactory* cf) {
		// TODO import deck from file
		std::cout << "reading deck\n";
		char chars[110], ca;
		in.getline(chars, 110);
		Card* card;
		for (int i = 6; i < in.gcount() - 1; i++) {
			ca = chars[i];
			card = ((CardFactory*)cf)->getCard(ca);
			push_back(card);
		}
	};
	/*Top of the deck is at the end of the vector*/
	Card* draw() {
		Card* c = back();
		pop_back();
		return c;
	};
	friend std::ostream& operator<<(std::ostream& os, Deck& deck) {
		deck.writeToFile(os);
		return os;
	};
	void writeToFile(std::ostream& os) {
		os << "Deck: ";
		for (Card* c : *this) {
			os << *c;
		}
		os << "\n";
	}
};

#pragma once
