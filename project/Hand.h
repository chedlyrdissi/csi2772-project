#include "CardFactory.h"
#include "./card/Card.h"
#include <list>
#include <cassert>

class Hand {
	// front | . | . | . | back
	std::list<Card*> cards;
public:
	Hand() {};
	Hand(std::istream& in, const CardFactory* cf) {
		// TODO implement
	};
	Hand& operator+=(Card* c) {
		cards.push_back(c);
		cards.sort(Card::compareCard);
		return *this;
	};
	Card* play() {
		Card* card = top();
		cards.pop_front();
		return card;
	};
	Card* top() {
		return cards.front();
	};
	Card* operator[](int i) {
		// assert(i >= 0 && i < cards.size());
		int j = 0;
		for (Card* c : cards) {
			if (i == j) {
				return c;
			}
			j++;
		}
		return NULL;
	};
	friend std::ostream& operator<<(std::ostream& os, const Hand& hand) {
		for (Card* c : hand.cards) {
			os << *c << " ";
		}
		return os;
	};
};

#pragma once
