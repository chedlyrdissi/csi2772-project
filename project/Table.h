#include "CardFactory.h"
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"

#include <string>


class Table {
	Player players[2];
	int currentPlayer = 0;
	Deck deck;
	DiscardPile discardPile;
	TradeArea tradeArea;
public:
	Table(std::string playerName1, std::string playerName2) {
		
	};
	
	Table(std::istream& in, const CardFactory* cf) : discardPile(in, cf), tradeArea(in, cf), deck(in, cf) {};
	
	void printHand(bool allHand) {
		players[currentPlayer].printHand(std::cout, allHand);
	}
	
	bool win(std::string& playerName) {
		// TODO implement
		int player;
		if (players[0].getName().compare(playerName) == 0) {
			player = 0;
		}
		else {
			player = 1;
		}
		// TODO check for ties
		return deck.empty() && players[player].getNumCoins() > players[(player + 1) % 2].getNumCoins();
	};
	
	friend std::ostream& operator<<(std::ostream& os, Table& table) {
		//	The two players,
		// the discard pile, the trading area should be printed.This is the top level print out
		os << table.players[0] << std::endl;
		os << table.players[1] << std::endl;
		table.discardPile.print(os);
		os << std::endl << table.tradeArea;
		return os;
	};
};

#pragma once
