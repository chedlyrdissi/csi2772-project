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
	Hand* hand;
public:
	Player(std::string& name): name(name), coins(0), nChains(0), maxChains(2) {
		for (int i = 0; i < 3; i++) {
			chains[i] = NULL;
		}
		hand = new Hand();
	};

	Player(std::istream& in, const CardFactory* cf) {
		// TODO implement
		std::cout << "reading player\n";

		/*
		os << "Player: " << name << "\n";
		os << "coins: " << coins << "\n";
		os << "nChains: " << nChains << "\n";
		os << "maxChains: " << maxChains << "\n";
		*/
		char buf[256];
		std::string bufs;
		
		in.getline(buf, 256); // read name
		name = "";
		for (int i = 8; i < in.gcount() - 1; i++) name += buf[i]; // create name
		
		in.getline(buf, 256); // read coins
		bufs = "";
		for (int i = 7; i < in.gcount() - 1; i++) bufs += buf[i]; // create coins
		coins = std::stoi(bufs);

		in.getline(buf, 256); // read nChains
		bufs = "";
		for (int i = 9; i < in.gcount() - 1; i++) bufs += buf[i]; // create nchains
		int bufnChains = std::stoi(bufs);
		
		in.getline(buf, 256); // read maxChains
		bufs = "";
		for (int i = 11; i < in.gcount() - 1; i++) bufs += buf[i]; // create maxChains
		maxChains = std::stoi(bufs);

		hand = new Hand(in, cf);
		// create chains
		Card* card;
		for (int i = 0; i < bufnChains; i++) {
			in.getline(buf, 256); // read chain
			if (in.gcount() <= 7) {
				// error
			}
			std::cout << buf[7] << "\n";
			card = ((CardFactory*)cf)->getCard(buf[7]);
			createChain(card);
			for (int j = 8; j < in.gcount() - 1; j++) {
				card = ((CardFactory*)cf)->getCard(buf[7]);
				chains[i]->addCard(card);
			}
		}
		
		std::cout << "reading chains\n";
	};


	~Player() {
		delete[] chains;
		delete hand;
	};
	
	std::string getName() {
		return name;
	};

	Hand& getHand() {
		return *hand;
	};
	
	int getNumCoins() {
		return coins;
	};

	int createChain(Card* c) {
		if (c->getName().compare("Blue") == 0) {
			return addChain(new Chain<Blue>(), c);
		}
		if (c->getName().compare("Chili") == 0) {
			return addChain(new Chain<Chili>(), c);
		}
		if (c->getName().compare("Stink") == 0) {
			return addChain(new Chain<Stink>(), c);
		}
		if (c->getName().compare("Green") == 0) {
			return addChain(new Chain<Green>(), c);
		}
		if (c->getName().compare("soy") == 0) {
			return addChain(new Chain<soy>(), c);
		};
		if (c->getName().compare("black") == 0) {
			return addChain(new Chain<black>(), c);
		}
		if (c->getName().compare("Red") == 0) {
			return addChain(new Chain<Red>(), c);
		}
		if (c->getName().compare("garden") == 0) {
			return addChain(new Chain<garden>(), c);
		}
		return -1;
	}
	
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
			os << *hand;
		}
		else {
			os << hand->top();
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
		}
		return os;
	}

	void writeToFile(std::ostream& os) {
		os << "Player: " << name << "\n";
		os << "coins: " << coins << "\n";
		os << "nChains: " << nChains << "\n";
		os << "maxChains: " << maxChains << "\n";
		hand->writeToFile(os);
		// write chain to file
		for (int i = 0; i < nChains; i++) {
			os << "chain: ";
			for (int j = 0; j < chains[i]->size(); j++) os << chains[i]->getChainName()[0];
			os << "\n";
		}
	}
};

#pragma once
