#include "Chain_Base.h"
#include "../card/Card.h"
#include "../CardFactory.h"
#include "../DiscardPile.h"
#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include "IllegalType.h"

template <class T>
class Chain: public virtual Chain_Base {
	std::vector<T*> cards;
public:
	Chain() {}
	
	Chain(std::istream& in, const CardFactory* cf) {
		char buf[256];
		Card* card;
		in.getline(buf, 256); // read chain
		if (in.gcount() <= 7) {
			// TODO error
		}
		for (int j = 7; j < in.gcount() - 1; j++) {
			card = ((CardFactory*)cf)->getCard(buf[7]);
			addCard(card);
		}
	}

	int size() {
		return cards.size();
	}

	void discard(DiscardPile& pile) {
		for (Card* c : cards) {
			pile += c;
		}
	}

	void addCard(Card* card) {
		T* c = dynamic_cast<T*>(card);
		if (c == nullptr) {
			throw IllegalType();
		}
		cards.push_back(c);
	}

	Chain<T>& operator+=(Card* c) {
		addCard(c);
		return *this;
	}
	
	int sell() {
		int coins = 0;
		if (!cards.empty()) {
			int cardsPerCoin;
			for (int necessaryCoins = 4; necessaryCoins > 0; necessaryCoins--) {
				// sell all
				cardsPerCoin = cards[0]->getCardsPerCoin(necessaryCoins);
				if (cards.size() >= cardsPerCoin) {
					coins = necessaryCoins;
					break;
				}
			}
		}
		return coins;
	};
	
	bool isEmpty() {
		return cards.size() == 0;
	};

	bool isMaxed() {
		return ((Card*)cards[0])->getCardsPerCoin(4) == cards.size();
	};
	
	std::string getChainName() {
		return ((Card*) cards[0])->getName();
	};

	void print(std::ostream& os) {
		if (!isEmpty()) {
			os << getChainName() << "\t";
			for (Card* c : cards) {
				os << *c << " ";
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& os, Chain<T>& chain) {
		chain.print(os);
		return os;
	}

	void writeToFile(std::ostream& os) {
		os << getChainName()[0] << " chain: ";
		for (Card* c : cards) {
			os << *c;
		}
		os << "\n";
	}
};

#pragma once
