#include <iostream>
#include <string.h>
#include "Card.h"
#include <cassert>

/*Concrete class for Card*/
class Chili : public virtual Card {
public:
	int getCardsPerCoin(int coins);
	std::string getName() const;
	void print(std::ostream& out);
};

inline int Chili::getCardsPerCoin(int coins) {
	assert((coins >= 0 && coins < 5));
	int cards = 0;
	switch (coins) {
	case 1: cards = 3; break;
	case 2: cards = 6; break;
	case 3: cards = 8; break;
	case 4: cards = 9; break;
	}
	return cards;
}

inline std::string Chili::getName() const {
	return "Chili";
}

inline void Chili::print(std::ostream& out) {
	out << "C";
}

#pragma once

