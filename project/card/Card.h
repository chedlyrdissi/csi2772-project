#include <iostream>
#include <string.h>

/*Base Card class*/
class Card {
public:
	virtual int getCardsPerCoin(int coins) = 0;
	virtual std::string getName() const = 0;
	virtual void print(std::ostream& out) {};
	friend std::ostream& operator<<(std::ostream& os, Card& card) {
		card.print(os);
		return os;
	};
	/*
	static bool compareCard(const Card* c1, const Card* c2) {
		return c1->getName().compare(c2->getName()) > 0;
	}
	*/
};

#pragma once
