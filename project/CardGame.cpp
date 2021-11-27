#include <iostream>
#include <string>
#include "CardFactory.h"
#include "TradeArea.h"
#include "./card/Card.h"
#include "Table.h"
#include <fstream>


using namespace std;





// define factory
CardFactory::CardFactory() {
	deck = new Deck();
	init();
};

void CardFactory::init() {
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
	for (int i = 0; i < 20; i++) {
		deck->push_back(new Blue());
	}
	for (int i = 0; i < 18; i++) {
		deck->push_back(new Chili());
	}
	for (int i = 0; i < 16; i++) {
		deck->push_back(new Stink());
	}
	for (int i = 0; i < 14; i++) {
		deck->push_back(new Green());
	}
	for (int i = 0; i < 12; i++) {
		deck->push_back(new soy());
	}
	for (int i = 0; i < 10; i++) {
		deck->push_back(new black());
	}
	for (int i = 0; i < 8; i++) {
		deck->push_back(new Red());
	}
	for (int i = 0; i < 6; i++) {
		deck->push_back(new garden());
	}
}

std::string CardFactory::getNameFromShortName(char shortName) {
	for (std::string s : validCards) {
		if (s[0] == shortName) {
			return s;
		}
	}
	return ""; // throw error
}

CardFactory* CardFactory::getFactory() {
	static CardFactory* instance = new CardFactory();
	return instance;
};

CardFactory::~CardFactory() {
	for (Card* card : *deck) {
		delete card;
	}
	delete deck;
};
/*
	returns a deck with all 104 bean cards.Note that the 104 bean cards are
	always the same but their order in the deck needs to be different every time.Use
	std::shuffle to achieve this.
*/
Deck& CardFactory::getDeck() {
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(deck->begin(), deck->end(), std::default_random_engine(seed));
	return *deck;
};

Card* CardFactory::getCard(char cardType) {
	Card* c = NULL;
	for (int i = 0; i < deck->size(); i++) {
		if ((*deck)[i]->getName().compare(getNameFromShortName(cardType)) == 0) {
			c = (*deck)[i];
			deck->erase(deck->begin() + i);
			break;
		}
	}
	// TODO throw corrupt save file error
	return c;
}







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
	Table* table = new Table(playerName1, playerName2);
	for (int i = 0; i < 2; i++) {
		for (int c = 0; c < 5; c++) {
			table->getPlayer(i).getHand() += table->getDeck().draw();
		}
	}
	cout << "New Game Starting" << endl << endl;
	return table;
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
	cout << "Resuming Game" << endl << endl;
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

int discardChainMenu(int maxChain) {
	cout << "Which chain would you like to discard ( between 1 and " << maxChain << " )" << endl;
	char c = '0';
	cin >> c;
	while (c <= '0' || c > char(maxChain)) {
		break;
	}
	return (c - '0') - 1;
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

void saveAndExit(Table& table) {
	string pathToFile;
	ofstream saveFile;

	cout << "Please input the save file path and name: ";
	cin >> pathToFile;
	saveFile.open(pathToFile);
	
	// write deck
	table.getDeck().writeToFile(saveFile);
	// write discard pile
	table.getDiscardPile().writeToFile(saveFile);
	// write trade area
	table.getTradeArea().writeToFile(saveFile);
	// write player 1
	table.getPlayer(0).writeToFile(saveFile);
	// write player 2
	table.getPlayer(1).writeToFile(saveFile);

	saveFile.close();
	cout << "Game Saved" << endl;
	cout << "Exiting";
}

bool isValidCard(char card) {
	for (string s: validCards) {
		if (s[0] == card) {
			return true;
		}
	}
	return false;
}

string cardCharToString(char card) {
	for (string s : validCards) {
		if (s[0] == card) {
			return s;
		}
	}
	return "";
}

string getTradeAreaCard() {
	char input = ' ';
	while (!isValidCard(input)) {
		cout << "Please select a Bean from the Trade Area: ";
		cin >> input;
	}
	return cardCharToString(input);
}

int continueDrawingFromTradeArea() {
	char input;
	cout << "Draw From Trade Area (y?)" << endl;
	cin >> input;
	return input == 'y';
}

bool playerWantToPlayMenu() {
	char c;
	cout << "Would you like to continue playing your hand (y?): ";
	cin >> c;
	return c == 'y';
}

int discardCardFromHandMenu(Hand& hand) {
	int i = -1;
	cout << hand << endl << "      ";
	for (int j = 0; j < hand.size(); j++) cout << j << " ";
	cout << endl;
	while (i < 0 && i >= hand.size()) {
		cout << "Please input a valid card index to discard : ";
		cin >> i;
	}
	return i;
}

int wantToDiscardFromHandMenu(Player* player) {
	cout << "Player " << player->getName() << ", would you like to discard a card from your hand (y?)?";
	char input;
	cin >> input;
	return input == 'y';
}

bool chainOrLeaveMenu(const string& card) {
	char c;
	cout << "Would you like to chain this card : " << card << " (y?) ? ";
	cin >> c;
	return c == 'y';
}

void sellMaxedChain(Player* player, DiscardPile& pile) {
	// check if chain ended
	int ichain = 0;
	while (ichain < player->getNumChains()) {
		if ((*player)[ichain].isMaxed()) {
			cout << "chain " << (*player)[ichain] << " maxed out\nHarvesting" << endl;
			// chain ended => sell it
			player->sellChain(ichain, pile);
			continue;
		}
		// move to next chain
		ichain++;
	}
}

int expandSlotsMenu(Player* player) {
	if (player->getNumCoins() < 3) return 0;
	if (player->getMaxNumChains() == 3) return 0;
	cout << "Would you like to buy a new slot for your chains (y?)";
	char input;
	cin >> input;
	if (input != 'y') return 0;
	player->buyThirdChain();
	return 1;
}

void harvestMenu(Player* player, DiscardPile& pile) {
	cout << "Harvest Time" << endl;
	cout << *player << endl;
	cout << "Please select a chain to harvest (1 to " << player->getNumChains() << ") ";
	char c;
	bool v;
	do {
		cin >> c;
		v = (c <= '0' || c > char(48 + player->getNumChains()));
	} while (v);
	int harvestIndex = (c - '0') - 1;
	player->sellChain(harvestIndex, pile);
}

void playCard(Player* player, Card* card, DiscardPile& pile) {
	// check if player has the corresponding chain
	if (player->canAddCard(card)) {
		// add it
		player->addToChain(card);
		return;
	}
	// offer to buy extra if player has no empty slot
	if (player->getMaxNumChains() == player->getNumChains() && !expandSlotsMenu(player)) {
		// harvest
		harvestMenu(player, pile);
	}
	// create new chain with card
	player->createChain(card);
	cout << *player << endl;
}

int main() {
	// Input the names of 2 players.Initialize the Deck and 
	// draw 5 cards for the Hand of each Player
	Table* table;
	if ( mainMenu() ) {
		table = initGame();
	}
	else {
		table = resumeGame();
	}

	Card* tradeAreaCard = NULL, *handCard = NULL;
	string selected;
	Player* player;
	int chainToHarvest, ichain, iCardToDiscardFromHand;
	bool playerWantToPlay;

	while (table->getDeck().size()) {
		// if pause save game to file and exit
		if (saveAndExitMenu()) {
			saveAndExit(*table);
			return 0;
		}
		for (int iplayer = 0; iplayer < 2; iplayer++) {
			player = table->nextPlayer();
			cout << endl << *table << endl;
			cout << "\n\t\t\t ~~~ Player " << player->getName() << "'s turn ~~~ \t\t\t" << endl << endl;
			player->getHand() += table->getDeck().draw();

			if (table->getTradeArea().numCards() != 0) {
				cout << "Trade Area has cards\n";
				cout << "You can select cards to add to your chains, all leftover cards are discarded.";
				do {
					// ask if wants to select cards from trade area
					tradeAreaCard = table->getTradeArea().trade(getTradeAreaCard());
					// if tradeAreaCard null, invalid choice
					if (tradeAreaCard == NULL) continue;
					// play card
					playCard(player, tradeAreaCard, table->getDiscardPile());
				} while (continueDrawingFromTradeArea() && table->getTradeArea().numCards() != 0);
				table->getTradeArea().discardAll(table->getDiscardPile()); // discard leftovers
				tradeAreaCard = NULL; // clean up
			}
			
			handCard = player->getHand().play();
			cout << "Playing card: " << *handCard << endl;
			playCard(player, handCard, table->getDiscardPile());

			// check if chain ended
			sellMaxedChain(player, table->getDiscardPile());

			player->printHand(cout, true);
			cout << endl;
			// check if player wants to play again
			if (playerWantToPlayMenu()) {
				handCard = player->getHand().play();
				cout << "Playing card: " << *handCard << endl;
				playCard(player, handCard, table->getDiscardPile());
			}

			// check if chain ended
			sellMaxedChain(player, table->getDiscardPile());

			if (wantToDiscardFromHandMenu(player)) {
				// give choice to discard a card
				iCardToDiscardFromHand = discardCardFromHandMenu(player->getHand());
				// cout << endl;
				handCard = player->getHand()[iCardToDiscardFromHand];
				player->getHand().remove(handCard); // remove from player's hand
				table->getDiscardPile() += handCard; // add to discard pile
				handCard = NULL; // clean up
				cout << endl;
			}

			// add 3 cards from deck to trade area
			cout << endl << "Adding 3 cards from deck to trade area\n";
			for (int i = 0; i < 3; i++) {
				if (table->getDeck().size() > 0) {
					tradeAreaCard = table->getDeck().draw();
					cout << "Drew " << tradeAreaCard->getName() << " From Deck, adding to trade area" << endl;
					table->getTradeArea() += tradeAreaCard;
					tradeAreaCard = NULL;
				}
			}
			cout << endl;

			// add cards from discard pile to trade area
			cout << "Adding cards from discard pile to trade area if possible" << endl;
			while (table->getDiscardPile().top() != NULL && table->getTradeArea().legal(table->getDiscardPile().top())) {
				cout << table->getDiscardPile() << endl;
				tradeAreaCard = table->getDiscardPile().pickUp();
				table->getTradeArea() += tradeAreaCard;
				tradeAreaCard = NULL;
			}

			// parse trade area
			cout << table->getTradeArea() << endl;
			for (int i = 0; i < table->getTradeArea().numCards();) {
				tradeAreaCard = table->getTradeArea()[i];
				if (chainOrLeaveMenu(tradeAreaCard->getName())) {
					table->getTradeArea().trade(tradeAreaCard->getName());
					playCard(player, tradeAreaCard, table->getDiscardPile());
					continue;
				}
				i++;
			}

			// draws 2 cards
			cout << "drawing 2 cards" << endl;
			for (int i = 0; i < 2; i++) {
				if (table->getDeck().size() > 0) {
					handCard = table->getDeck().draw();
					cout << "Drew " << handCard->getName() << " From Deck, adding to Hand" << endl;
					player->getHand() += handCard;
					handCard = NULL;
				}
			}
		}
	}

	// check winner
	Player player1 = table->getPlayer(0);
	Player player2 = table->getPlayer(1);
	cout << "GAME OVER\n";
	cout << "\tPlayer 1: " << (table->win(player1.getName())? "wins": "loses") << "\n";
	cout << "\tPlayer 2: " << (table->win(player2.getName()) ? "wins" : "loses") << "\n";
	return 0;
}
