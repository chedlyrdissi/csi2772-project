#include <iostream>
#include <string.h>
#include "Card.h"
#include <cassert>

/*Concrete class for Card*/
class Soy : public virtual Card {
public:
	int getCardsPerCoin(int coins);
	std::string getName() const;
	void print(std::ostream& out);
};

inline int Soy::getCardsPerCoin(int coins) {
	assert((coins >= 0 && coins < 5));
	int cards = 0;
	switch (coins) {
	case 1: cards = 2; break;
	case 2: cards = 4; break;
	case 3: cards = 6; break;
	case 4: cards = 7; break;
	}
	return cards;
}

inline std::string Soy::getName() const {
	return "soy";
}

inline void Soy::print(std::ostream& out) {
	out << "s";
}

#pragma once

