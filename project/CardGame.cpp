#include <iostream>
#include <string>
#include "CardFactory.h"
#include "TradeArea.h"
#include "./card/Card.h"
#include "Table.h"
#include <fstream>


using namespace std;

const string validCards[8] = { "Blue", "Chili", "Stink", "Green", "soy", "black", "Red", "garden" };

string getInputPlayerName(int player) {
	cout << "Please enter the name of player " << player << endl;
	string name;
	cin >> name;
	return name;
}

Table* initGame() {
	string playerName1 = getInputPlayerName(1);
	string playerName2 = getInputPlayerName(2);
	return new Table(playerName1, playerName2);
}

Table* resumeGame() {
	// ask for file
	string pathToFile;
	ifstream* saveFile = NULL;
	do {
		cout << "Please input the path to a save file: ";
		cin >> pathToFile;
		saveFile = new ifstream(pathToFile);
		if (!(saveFile->good())) {
			cout << "invalid file" << endl;
			delete saveFile;
			saveFile = NULL;
		}
	} while (saveFile == NULL);
	Table* newTable = new Table(*saveFile, CardFactory::getFactory());
	string line;
	while ( getline(*saveFile, line) ) {
		cout << line << endl;
	}
	saveFile->close();
	delete saveFile;
	return newTable;
}

bool mainMenu() {
	cout << "Welcome to BEANS the card game! (not kidding)" << endl;
	char c = '0';
	while (c != '1' && c != '2') {
		cout << "\t1) Start New Game" << endl;
		cout << "\t2) Load Game" << endl;
		cin >> c;
	}
	return c == '1';
}

bool saveAndExitMenu() {
	char c = '0';
	while (c != '1' && c != '2') {
		cout << "\t1) Continue" << endl;
		cout << "\t2) Save and Exit" << endl;
		cin >> c;
	}
	return c == '2';
}

void saveAndExit() {}

bool isValidCard(const string& card) {
	for (string s: validCards) {
		if (s.compare(card) == 0) {
			return true;
		}
	}
	return false;
}

string getTradeAreaCard() {
	string input = "";
	while (!isValidCard(input)) {
		cout << "Please select a Bean" << endl;
		cin >> input;
	}
	return input;
}

int main() {
	// Input the names of 2 players.Initialize the Deck and 
	// draw 5 cards for the Hand of each Player
	/*
	CardFactory* cardFactory = CardFactory::getFactory();
	string player1Name = getInputPlayerName(1);
	string player2Name = getInputPlayerName(2);
	Player players[2] = { player1Name, player2Name };
	Deck deck = cardFactory->getDeck();
	Table table;
	TradeArea tradeArea;
	*/
	Table* table;
	if ( mainMenu() ) {
		table = initGame();
	}
	else {
		table = resumeGame();
	}
	/*
	Card* tradeAreaCard;
	string selected;
	while (table->deck.empty()) {
		// if pause save game to file and exit
		if (saveAndExitMenu()) {
			saveAndExit();
			break;
		}
		for (Player player: players) {
			cout << table << endl;
			player.getHand() += deck.draw();
			if ( tradeArea.numCards() != 0 ) {
				// Add bean cards from the TradeArea to chains or discard them.
				// player has chains
				// check the chains if cards exist => trade
				// or discard what's left
				selected = getTradeAreaCard();
				tradeAreaCard = tradeArea.trade(selected);
				for (int ichain = 0; ichain < player.getMaxNumChains(); ichain++) {
					if (player[ichain].isEmpty()) { // no chain has this bean
						// create a chain
						player[ichain];
						// link it to player
					}
					else {
						// check if tradeAreaCard is valid
						// while (tradeAreaCard = tradeArea.trade("") != NULL) {}
					}
				}
				
			}
		}
	}
	*/
}
