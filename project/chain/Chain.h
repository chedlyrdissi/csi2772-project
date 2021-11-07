#include "Chain_Base.h"
#include "../card/Card.h"
#include "../CardFactory.h"
#include <vector>
#include <iostream>

template <class T>
class Chain: public virtual Chain_Base {
	std::vector<T*> cards;
public:
	Chain() {}
	Chain(std::istream& in, const CardFactory* cf) {
		// TODO implement
	}
	Chain<T>& operator+=(Card* c) {
		return *this;
	}
	int sell();
	friend std::ostream& operator<<(std::ostream& os, const Chain<T>& chain);
};

template <class T>
int Chain<T>::sell() {
	return 0;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Chain<T>& chain) {
	if (!chain.cards.empty()) {
		os << chain.cards[0]->getName() << " ";
		for (Card* c: chain.cards) {
			os << c << " ";
		}
	}
	return os;
}

#pragma once
