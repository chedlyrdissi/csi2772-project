#include <iostream>
#include <string.h>
#include "Card.h"
#include <cassert>

/*Concrete class for Card*/
class Blue : public virtual Card {
public:
	int getCardsPerCoin(int coins);
	std::string getName();
	void print(std::ostream& out);
};

inline int Blue::getCardsPerCoin(int coins) {
	assert((coins >= 0 && coins < 5));
	int cards = 0;
	switch (coins) {
	case 1: cards = 4; break;
	case 2: cards = 6; break;
	case 3: cards = 8; break;
	case 4: cards = 10; break;
	}
	return cards;
}

inline std::string Blue::getName() {
	return "Blue";
}

inline void Blue::print(std::ostream& out) {
	out << "B";
}

#pragma once

