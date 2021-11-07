#include <iostream>
#include <string>
#include "./chain/Chain.h"
#include "./card/Card.h"
#include "Hand.h"
#include "NotEnoughCoins.h"

class Player {
	std::string name;
	int coins;
	int nChains;
	Chain<Card*> chains[3];
	Hand hand;
public:
	Player(std::string&);
	Player(std::istream& in, const CardFactory* cf);
	std::string getName();
	int getNumCoins();
	Player& operator+=(int);
	int getMaxNumChains();
	int getNumChains();
	Chain<Card*>& operator[](int i);
	void buyThirdChain();
	void printHand(std::ostream&, bool);
	friend std::ostream& operator<<(std::ostream& os, const Player& player);
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
	/* TODO check if chain has size or extends vector
	for (int i = 0; i < nChains; i++) {
		if (chains)
	}
	*/
	return res;
}

void Player::buyThirdChain() {
	if (coins < 2) throw NotEnoughCoins();
	if (nChains < 3) {
		coins--;
		nChains++;
	}
}

void Player::printHand(std::ostream& os, bool allHand) {
	if (allHand) {
		os << hand;
	}
	else {
		os << hand.top();
	}
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
	/*
		Dave 3 coins
		Red R R R R
		Blue B
	*/
	os << player.name << " " << player.coins << " coins" << std::endl;
	for (int i = 0; i < player.nChains; i++) {
		os << player.chains << std::endl;
		// os << player.chains[i] << std::endl;
	}
	return os;
}

#pragma once
