#include "Deck.h"
#include <vector>

class CardFactory {
	std::vector<Card*> cards;
	static CardFactory* instance;
	CardFactory();
public:
	static CardFactory* getFactory() {
		if (instance == NULL)
			instance = new CardFactory();
		return instance;
	}
	/*
	 returns a deck with all 104 bean cards.Note that the 104 bean cards are
		always the same but their order in the deck needs to be different every time.Use
		std::shuffle to achieve this.
	*/
	Deck getDeck();
};

CardFactory::CardFactory() {
	/*
		Blue 20
		Chili 18
		Stink 16
		Green 14
		soy 12
		black 10
		Red 8
		garden 6
	*/
}

#pragma once