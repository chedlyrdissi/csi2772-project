#include <iostream>
#include <string.h>
#include "Card.h"
#include <cassert>

/*Concrete class for Card*/
class Garden : public virtual Card {
public:
	int getCardsPerCoin(int coins);
	std::string getName() const;
	void print(std::ostream& out);
};

inline int Garden::getCardsPerCoin(int coins) {
	assert((coins >= 0 && coins < 5));
	int cards = 0;
	switch (coins) {
	case 1: cards = 0; break;
	case 2: cards = 2; break;
	case 3: cards = 3; break;
	case 4: cards = 0; break;
	}
	return cards;
}

inline std::string Garden::getName() const {
	return "garden";
}

inline void Garden::print(std::ostream& out) {
	out << "g";
}

#pragma once

