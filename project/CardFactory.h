// #include "Deck.h"
#include "./card/black.h"
#include "./card/Red.h"
#include "./card/Green.h"
#include "./card/Blue.h"
#include "./card/Chili.h"
#include "./card/garden.h"
#include "./card/soy.h"
#include "./card/Stink.h"
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <time.h>
#include <string>

class Deck;

class CardFactory {
	Deck* deck;

	const std::string validCards[8] = { "Blue", "Chili", "Stink", "Green", "soy", "black", "Red", "garden" };

	CardFactory();
	
	void init();

	std::string getNameFromShortName(char shortName);

public:
	static CardFactory* getFactory();

	~CardFactory();
	/*
	 returns a deck with all 104 bean cards.Note that the 104 bean cards are
		always the same but their order in the deck needs to be different every time.Use
		std::shuffle to achieve this.
	*/
	Deck& getDeck();

	Card* getCard(char cardType);
};

#pragma once
