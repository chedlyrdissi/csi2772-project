#include <iostream>
#include <string.h>

/*Base Card class*/
class Card {
public:
	virtual int getCardsPerCoin(int coins) = 0;
	virtual std::string getName() = 0;
	virtual void print(std::ostream& out) {};
	friend std::ostream& operator<<(std::ostream& os, Card& card);
};

inline std::ostream& operator <<(std::ostream& os, Card& card) {
	card.print(os);
	return os;
}

#pragma once
