#include "Deck.h"
/*
#include "./card/black.h"
#include "./card/Red.h"
#include "./card/Green.h"
#include "./card/Blue.h"
#include "./card/Chili.h"
#include "./card/garden.h"
#include "./card/soy.h"
*/
#include "./card/Stink.h"
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <time.h>

class CardFactory {
	Deck deck;
	// static CardFactory* instance;
	CardFactory() {
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
		/*
		for (int i = 0; i < 20; i++) {
			deck.push_back(new Blue());
		}
		for (int i = 0; i < 18; i++) {
			deck.push_back(new Chili());
		}
		*/
		/*
		for (int i = 0; i < 16; i++) {
			deck.push_back(new Stink());
		}
		for (int i = 0; i < 14; i++) {
			deck.push_back(new Green());
		}
		for (int i = 0; i < 12; i++) {
			deck.push_back(new soy());
		}
		for (int i = 0; i < 10; i++) {
			deck.push_back(new black());
		}
		for (int i = 0; i < 8; i++) {
			deck.push_back(new Red());
		}
		for (int i = 0; i < 60; i++) {
			deck.push_back(new garden());
		}
		*/
		};
public:
	static CardFactory* getFactory() {
		// if (instance == NULL)
		//	instance = new CardFactory();
		static CardFactory* instance = new CardFactory();
		return instance;
	};
	~CardFactory() {
		for (Card* card : deck) {
			delete card;
		}
	};
	/*
	 returns a deck with all 104 bean cards.Note that the 104 bean cards are
		always the same but their order in the deck needs to be different every time.Use
		std::shuffle to achieve this.
	*/
	Deck getDeck() {
		unsigned int seed = 0; // time(NULL); //std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
		return deck;
	};
};

#pragma once
