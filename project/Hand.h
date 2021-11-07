#include "CardFactory.h"
#include "./card/Card.h"
#include <list>
#include <cassert>

class Hand {
	// front | . | . | . | back
	std::list<Card*> cards;
public:
	Hand() {};
	Hand(std::istream&, const CardFactory*);
	Hand& operator+=(Card*);
	Card* play();
	Card* top();
	Card* operator[](int);
	friend std::ostream& operator<<(std::ostream& os, const Hand& hand);
};

Hand::Hand(std::istream& in, const CardFactory* cf) {
	// TODO implement
}

Hand& Hand::operator+=(Card* c) {
	cards.push_back(c);
	cards.sort(compareCard);
	return *this;
}

Card* Hand::play() {
	Card* card = top();
	cards.pop_front();
	return card;
}

Card* Hand::top() {
	return cards.front();
}

Card* Hand::operator[](int i) {
	// assert(i >= 0 && i < cards.size());
	int j = 0;
	for (Card* c : cards) {
		if ( i == j) {
			return c;
		}
		j++;
	}
	return NULL;
}

std::ostream& operator<<(std::ostream& os, const Hand& hand) {
	for (Card* c : hand.cards) {
		os << *c << " ";
	}
	return os;
}

#pragma once
