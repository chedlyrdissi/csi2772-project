#include "Chain_Base.h"
#include "../card/Card.h"
#include "../CardFactory.h"
#include <vector>
#include <string>
#include <iostream>
#include <type_traits>

template <class T>
class Chain: public virtual Chain_Base {
	// static_assert(std::is_base_of<Card, T>::value, "T must inherit from Card");
	std::vector<T*> cards;
public:
	Chain() {}
	Chain(std::istream& in, const CardFactory* cf) {
		// TODO implement
	}
	Chain<T>& operator+=(T* c) {
		cards.push_back(c);
		return *this;
	}
	Chain<T>& operator=(Chain<T> chain) {
		this->cards = chain.cards;
		return *this;
	}
	int sell();
	bool isEmpty() {
		return cards.empty();
	};
	std::string getChainName() {
		return ((Card*) cards[0])->getName();
	};
	friend std::ostream& operator<<(std::ostream& os, Chain<T>& chain) {
		if (!chain.isEmpty()) {
			os << chain.getChainName() << "\t";
			for (Card* c: chain.cards) {
				os << *c << " ";
			}
		}
		return os;
	}
};

template <class T>
int Chain<T>::sell() {
	int coins = 0;
	if (!isEmpty()) {
		int cardsPerCoin;
		for (int necessaryCoins = 4; necessaryCoins > 0; necessaryCoins--) {
			// TODO does it leave cards in chain or sell all or nothing
			cardsPerCoin = cards[0]->getCardsPerCoin(necessaryCoins)
			if (cards.size() >= cardsPerCoin) {
				coins = necessaryCoins;
				for (int i = 0; i < cardsPerCoin; i++) {
					cards.pop_back();
				}
			}
		}
	}
	return coins;
}

#pragma once
