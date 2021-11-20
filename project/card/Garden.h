#include <iostream>
#include <string.h>
#include "Card.h"
#include <cassert>

/*Concrete class for Card*/
class garden : public virtual Card {
public:
	int getCardsPerCoin(int coins) {
		assert((coins >= 0 && coins < 5));
		int cards = 999;
		switch (coins) {
		case 2: cards = 2; break;
		case 3: cards = 3; break;
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
