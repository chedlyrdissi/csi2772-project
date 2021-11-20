#include "CardFactory.h"
#include "./card/Card.h"
#include <list>
#include <assert.h>

class Hand : public std::list<Card*> {
	// front | . | . | . | back
	// std::list<Card*> cards;
public:
	Hand() {};
	
	Hand(std::istream& in, const CardFactory* cf) {
		// TODO implement
	};
	
	Hand& operator+=(Card* c) {
		// cards.push_back(c);
		push_back(c);
		return *this;
	};
	
	Card* play() {
		Card* card = top();
		// cards.pop_front();
		pop_front();
		return card;
	};

	Card* top() {
		// return cards.front();
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
		for (Card* c : hand) {
			os << *c << " ";
		}
		return os;
	};
};

#pragma once
