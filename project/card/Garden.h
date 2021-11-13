#include <iostream>
#include <string.h>
#include "Card.h"
#include <cassert>

/*Concrete class for Card*/
class garden : public virtual Card {
public:
	int getCardsPerCoin(int coins) {
		assert((coins >= 0 && coins < 5));
		int cards = 0;
		switch (coins) {
		case 1: cards = 0; break;
		case 2: cards = 2; break;
		case 3: cards = 3; break;
		case 4: cards = 0; break;
		}
		return cards;
	};
	std::string getName() const {
		return "garden";
	}
	void print(std::ostream& out) {
		out << "g";
	}
};

#pragma once
