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
	Player(std::string&);
	Player(std::istream& in, const CardFactory* cf);
	std::string getName();
	int getNumCoins();
	Player& operator+=(int);
	Player& operator=(const Player&);
	int getMaxNumChains();
	int getNumChains();
	Chain<Card>& operator[](int i);
	void buyThirdChain();
	void printHand(std::ostream&, bool);
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

Player::Player(std::string& name): name(name), coins(0), nChains(2) {}

Player::Player(std::istream& in, const CardFactory* cf): coins(0), nChains(2) {
	// TODO implement
}

std::string Player::getName() {
	return name;
}

int Player::getNumCoins() {
	return coins;
}

int Player::getMaxNumChains() {
	return nChains;
}

int Player::getNumChains() {
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
}

void Player::buyThirdChain() {
	if (coins < 2) throw NotEnoughCoins();
	if (nChains < 3) {
		coins--;
		nChains++;
	}
}

Player& Player::operator+=(int coins) {
	this->coins += coins;
	return *this;
}

Player& Player::operator=(const Player& player) {
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
}

Chain<Card>& Player::operator[](int i) {
	// TODO assert i
	return chains[i];
}

void Player::printHand(std::ostream& os, bool allHand) {
	if (allHand) {
		os << hand;
	}
	else {
		os << hand.top();
	}
}

#pragma once
