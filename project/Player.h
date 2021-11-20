#include <iostream>
#include <string>
#include <assert.h>
#include "./chain/Chain_Base.h"
#include "./chain/Chain.h"
#include "./card/Card.h"
#include "Hand.h"
#include "NotEnoughCoins.h"
#include "DiscardPile.h"

class Player {
	std::string name;
	int coins;
	int nChains;
	int maxChains; // max num of chains available 2 or 3
	Chain_Base* chains[3];
	Hand hand;
public:
	Player(std::string& name) : name(name), coins(0), nChains(0), maxChains(2) {
		for (int i = 0; i < 3; i++) {
			chains[i] = NULL;
		}
	};
	
	Player(std::istream& in, const CardFactory* cf) {
		// TODO implement
	};
	
	std::string getName() {
		return name;
	};

	Hand& getHand() {
		return hand;
	};
	
	int getNumCoins() {
		return coins;
	};
	
	Player& operator+=(int coins) {
		this->coins += coins;
		return *this;
	};
	
	Player& operator=(const Player& player) {
		if (&player != this) {
			this->name = player.name;
			this->coins = player.coins;
			this->nChains = player.nChains;
			this->maxChains = player.maxChains;
			for (int i = 0; i < 3; i++) {
				this->chains[i] = player.chains[i];
			}
			this->hand = player.hand;
		}
		return *this;
	};
	
	int getMaxNumChains() {
		return maxChains;
	};

	int getNumChains() {
		return nChains;
	};

	int addChain(Chain_Base *chain, Card* c) {
		assert(nChains < maxChains);
		chains[nChains++] = chain;
		chains[nChains-1]->addCard(c);
		return nChains;
	}

	void setNumChains(int nChains) {
		assert(nChains <= this->maxChains);
		this->nChains = nChains;
	};

	Chain_Base& operator[](int i) {
		assert(i >= 0 && i < nChains);
		return *chains[i];
	};

	int setnChains(int nchains) {
		this->nChains = nchains;
	}

	void sellChain(int ichain, DiscardPile& pile) {
		assert(ichain >= 0 && ichain < nChains);
		int coins = chains[ichain]->sell();
		
		// discard cards
		chains[ichain]->discard(pile);

		// kill object
		delete chains[ichain];

		// fill void
		chains[ichain] = chains[nChains - 1];
		chains[nChains - 1] = NULL;
		nChains--;
		(*this) += coins;
	}

	void buyThirdChain() {
		if (coins < 2) throw NotEnoughCoins();
		if (maxChains < 3) {
			coins--;
			maxChains++;
		}
	};

	void printHand(std::ostream& os, bool allHand) {
		if (allHand) {
			os << hand;
		}
		else {
			os << hand.top();
		}
	};

	friend std::ostream& operator<<(std::ostream& os, Player& player) {
		/*
			Dave 3 coins
			Red R R R R
			Blue B
		*/
		os << player.name << " " << player.coins << " coins" << std::endl;
		for (int i = 0; i < player.getNumChains(); i++) {
			os << *(player.chains[i]) << std::endl;
			// os << *(dynamic_cast<Chain<Card>*>((player.chains[i]))) << std::endl;
			// os << *((Chain<Card>*) player.chains[i]) << std::endl;
		}
		return os;
	}
};

#pragma once
