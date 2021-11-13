#include <iostream>
#include <string>
#include "./chain/Chain.h"
#include "./card/Card.h"
#include "Hand.h"
#include "NotEnoughCoins.h"

class Player {
	std::string name;
	int coins = 0;
	int nChains = 2; // max num of chains available
	Chain<Card> chains[3];
	Hand hand;
public:
	Player() {};
	Player(std::string& name): name(name), coins(0), nChains(2) {};
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
			for (int i = 0; i < 3; i++) {
				this->chains[i] = player.chains[i];
			}
			this->hand = player.hand;
		}
		return *this;
	};
	int getMaxNumChains() {
		return nChains;
	};
	int getNumChains() {
		int res = 0;
		for (int i = 0; i < nChains; i++) {
			if (chains[i].isEmpty()) {
				break;
			}
			else {
				res++;
			}
		}
		return res;
	};
	Chain<Card>& operator[](int i) {
		// TODO assert i
		return chains[i];
	};
	void buyThirdChain() {
		if (coins < 2) throw NotEnoughCoins();
		if (nChains < 3) {
			coins--;
			nChains++;
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
		os << "nchains " << player.getNumChains() << std::endl;
		for (int i = 0; i < player.getNumChains(); i++) {
			os << player.chains[i] << std::endl;
		}
		return os;
	}
};

#pragma once
