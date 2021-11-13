#include <iostream>
#include <string.h>
#include "Card.h"
#include <cassert>

/*Concrete class for Card*/
class black : public virtual Card {
public:
	int getCardsPerCoin(int coins) {
		assert((coins >= 0 && coins < 5));
		int cards = 0;
		switch (coins) {
		case 1: cards = 2; break;
		case 2: cards = 4; break;
		case 3: cards = 5; break;
		case 4: cards = 6; break;
		}
		return cards;
	};
	std::string getName() const {
		return "black";
	};
	void print(std::ostream& out) {
		out << "b";
	};
};

#pragma once
