#include <iostream>
#include <string.h>
#include "Card.h"
#include <cassert>

/*Concrete class for Card*/
class Green : public virtual Card {
public:
	int getCardsPerCoin(int coins);
	std::string getName();
	void print(std::ostream& out);
};

inline int Green::getCardsPerCoin(int coins) {
	assert((coins >= 0 && coins < 5));
	int cards = 0;
	switch (coins) {
	case 1: cards = 3; break;
	case 2: cards = 5; break;
	case 3: cards = 6; break;
	case 4: cards = 7; break;
	}
	return cards;
}

inline std::string Green::getName() {
	return "Green";
}

inline void Green::print(std::ostream& out) {
	out << "G";
}

#pragma once

