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
		nChains = std::stoi(bufs);
		
		in.getline(buf, 256); // read maxChains
		bufs = "";
		for (int i = 11; i < in.gcount() - 1; i++) bufs += buf[i]; // create maxChains
		maxChains = std::stoi(bufs);

		hand = new Hand(in, cf);
		// create chains
		char type;
		for (int i = 0; i < nChains; i++) {
			// create chain
			// addit
			in.get(type);
			in.get(); // jump the space
			switch (type) {
				case 'B': chains[i] = new Chain<Blue>(in, cf); break;
				case 'b': chains[i] = new Chain<black>(in, cf); break;
				case 'R': chains[i] = new Chain<Red>(in, cf); break;
				case 'G': chains[i] = new Chain<Green>(in, cf); break;
				case 'g': chains[i] = new Chain<garden>(in, cf); break;
				case 's': chains[i] = new Chain<soy>(in, cf); break;
				case 'S': chains[i] = new Chain<Stink>(in, cf); break;
				case 'C': chains[i] = new Chain<Chili>(in, cf); break;
			}
		}
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

	int canAddCard(Card* card) {
		for (Chain_Base* chain : chains) {
			if (chain != NULL && chain->getChainName().compare(card->getName()) == 0) {
				return 1;
			}
		}
		return 0;
	}

	void addToChain(Card* card) {
		if (card != NULL && canAddCard(card)) {
			for (Chain_Base* chain : chains) {
				if (chain != NULL && chain->getChainName().compare(card->getName()) == 0) {
					*chain += card;
					return;
				}
			}
		}
		// TODO throw error
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
			chains[i]->writeToFile(os);
		}
	}
};

#pragma once
