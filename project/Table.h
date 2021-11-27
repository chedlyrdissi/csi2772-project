#include "CardFactory.h"
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include <string>

#include <iostream>

class Table {
	Player* players[2];
	int currentPlayer = 0;
	Deck deck;
	DiscardPile discardPile;
	TradeArea tradeArea;
public:
	Table(std::string playerName1, std::string playerName2) {
		players[0] = new Player(playerName1);
		players[1] = new Player(playerName2);
		deck = CardFactory::getFactory()->getDeck();
	};
	
	Table(std::istream& in, const CardFactory* cf) : discardPile(in, cf), tradeArea(in, cf), deck(in, cf) {
		players[0] = new Player(in, cf);
		players[1] = new Player(in, cf);
	};

	~Table() {
		delete players[0];
		delete players[1];
	}
	
	Player** getPlayers() {
		return players;
	};

	Player& getPlayer(int player) {
		assert(player == 0 or player == 1);
		return *(players[player]);
	};

	int& getCurrentPlayer() {
		return currentPlayer;
	}

	Deck& getDeck() {
		return deck;
	};
	
	DiscardPile& getDiscardPile() {
		return discardPile;
	};
	
	TradeArea& getTradeArea() {
		return tradeArea;
	};

	void printHand(bool allHand) {
		players[currentPlayer]->printHand(std::cout, allHand);
	}

	Player* nextPlayer() {
		return players[currentPlayer++ % 2];
	}
	
	bool win(const std::string& playerName) {
		int player;
		if (players[0]->getName().compare(playerName) == 0) {
			player = 0;
		}
		else {
			player = 1;
		}
		// TODO check for ties
		return deck.empty() && players[player]->getNumCoins() > players[(player + 1) % 2]->getNumCoins();
	};
	
	friend std::ostream& operator<<(std::ostream& os, Table& table) {
		//	The two players,
		// the discard pile, the trading area should be printed.This is the top level print out
		os << "Table:-------------------------------------------------------------------------\n";
		os << "\n";
		os << *(table.players[0]) << std::endl;
		os << *(table.players[1]) << std::endl;
		table.discardPile.print(os);
		os << std::endl;
		os << table.tradeArea;
		os << "\n-------------------------------------------------------------------------------\n";
		return os;
	};
};

#pragma once
