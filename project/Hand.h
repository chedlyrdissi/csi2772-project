#include "CardFactory.h"
#include "./card/Card.h"
#include <list>
#include <assert.h>

#include <iostream>

class Hand : public std::list<Card*> {
	// front | . | . | . | back
	// std::list<Card*> cards;
public:
	Hand() {};
	
	Hand(std::istream& in, const CardFactory* cf) {
		char chars[110], ca;
		in.getline(chars, 110);
		Card* card;
		for (int i = 6; i < in.gcount() - 1; i++) {
			ca = chars[i];
			card = ((CardFactory*)cf)->getCard(ca);
			push_back(card);
		}
	};
	
	Hand& operator+=(Card* c) {
		push_back(c);
		return *this;
	};
	
	Card* play() {
		Card* card = top();
		pop_front();
		return card;
	};

	Card* top() {
		return front();
	};
	
	Card* operator[](int i) {
		assert(i >= 0 && i < size());
		int j = 0;
		for (Card* c : *this) {
			if (i == j) {
				return c;
			}
			j++;
		}
		return NULL;
	};

	friend std::ostream& operator<<(std::ostream& os, const Hand& hand) {
		os << "Hand: ";
		for (Card* c : hand) {
			os << *c << " ";
		}
		return os;
	};

	void writeToFile(std::ostream& os) {
		os << "Hand: ";
		for (Card* c : *this) {
			os << *c;
		}
		os << "\n";
	}
};

#pragma once
