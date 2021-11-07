#include <iostream>
#include <string.h>
#include "Card.h"
#include <cassert>

/*Concrete class for Card*/
class Stink : public virtual Card {
public:
	int getCardsPerCoin(int coins);
	std::string getName() const;
	void print(std::ostream& out);
};

inline int Stink::getCardsPerCoin(int coins) {
	assert((coins >= 0 && coins < 5));
	int cards = 0;
	switch (coins) {
	case 1: cards = 3; break;
	case 2: cards = 5; break;
	case 3: cards = 7; break;
	case 4: cards = 8; break;
	}
	return cards;
}

inline std::string Stink::getName() const {
	return "Stink";
}

inline void Stink::print(std::ostream& out) {
	out << "S";
}

#pragma once
