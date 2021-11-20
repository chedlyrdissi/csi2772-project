#include "./card/Card.h"
#include "DiscardPile.h"
#include <vector>

class Chain_Base {
public:
	Chain_Base() {};
	virtual ~Chain_Base() {};
	virtual int sell() = 0;
	virtual bool isMaxed() = 0;
	virtual void addCard(Card*) = 0;
	virtual void discard(DiscardPile& pile) = 0;
	virtual std::string getChainName() = 0;
	virtual void print(std::ostream&) = 0;
	friend std::ostream& operator<<(std::ostream& os, Chain_Base& chain) {
		chain.print(os);
		return os;
	};
};

#pragma once
