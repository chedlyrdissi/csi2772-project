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

	cout << "Please input the save file name: ";
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
	// write hand
	// write chains
	// write player 2
	table.getPlayer(1).writeToFile(saveFile);
	// write hand
	// write chains

	saveFile.close();
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

/*
* true to add card to chain
*/
bool getTradeAreaCardChoice(const string& cardType) {
	char c = ' ';
	while (c != '1' && c != '2') {
		cout << "What would you like to do with this card: " << cardType << endl;
		cout << "\t1) add to chain(s)" << endl;
		cout << "\t2) discard" << endl;
		cin >> c;
	}
	return c == '1';
}

Card* addToChainIfPossible(Player* player, Card* card) {
	// parse chains to add card
	for (int i = 0; i < player->getNumChains(); i++) {
		if (card != NULL && (*player)[i].getChainName().compare(card->getName()) == 0) {
			(*player)[i].addCard(card);
			card = NULL;
		}
	}

	if (card != NULL && player->getNumChains() != player->getMaxNumChains()) {
		player->createChain(card);
		card = NULL;
	}

	return card;
}

bool playerWantToPlayMenu() {
	char c = ' ';
	while (c != '2' && c != '1') {
		cout << "Would you like to continue playing your hand: " << endl;
		cout << "\t1) Continue\n";
		cout << "\t2) Do not continue\n";
		cin >> c;
	}
	return c == '1';
}

int discardCardIndexFromHandMenu(Hand& hand) {
	int i = -2;
	cout << hand << endl;
	for (int j = 0; j < hand.size(); j++) cout << j << " ";
	cout << endl;
	while (i < -1 && i >= hand.size()) {
		cout << "Please input a card index to discard : ";
		cin >> i;
	}
	return i;
}

bool chainOrLeaveMenu(const string& card) {
	char c = ' ';
	while (c != '2' && c != '1') {
		cout << "Would you like to chain this card : ( " << card << " )" << endl;
		cout << "\t1) yes\n";
		cout << "\t2) no\n";
		cin >> c;
	}
	return c == '1';
}

void sellMaxedChain(Player* player, DiscardPile& pile) {
	// check if chain ended
	int ichain = 0;
	while (ichain < player->getNumChains()) {
		if ((*player)[ichain].isMaxed()) {
			cout << "chain maxed out " << (*player)[ichain] << " => Harvesting" << endl;
			// chain ended => sell it
			player->sellChain(ichain, pile);
		}
		else {
			// move to next chain
			ichain++;
		}
	}
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

	Card* tradeAreaCard = NULL, *handCard;
	string selected;
	Player* player;
	int chainToHarvest, ichain, iCardToDiscardFromHand;
	bool playerWantToPlay;

	while (table->getDeck().size()) {
		// if pause save game to file and exit
		if (saveAndExitMenu()) {
			saveAndExit(*table);
			break;
		}
		for (int iplayer = 0; iplayer < 2; iplayer++) {
			player = table->nextPlayer();
			cout << endl << *table << endl;
			player->getHand() += table->getDeck().draw();

			// check trade area
			while (table->getTradeArea().numCards() != 0 ) {
				cout << "Hand of " << player->getName() << ": ";
				player->printHand(cout, true);
				cout << endl << endl;
				// Add bean cards from the TradeArea to chains or discard them.
				while (tradeAreaCard == NULL) {
					selected = getTradeAreaCard();
					tradeAreaCard = table->getTradeArea().trade(selected);
				}
				
				if (getTradeAreaCardChoice(tradeAreaCard->getName())) {
					// add to chain if possible
					tradeAreaCard = addToChainIfPossible(player, tradeAreaCard);
					// check if chain ended TODO check if this is valid
					sellMaxedChain(player, table->getDiscardPile());
					if (tradeAreaCard != NULL) {
						if (player->getNumChains() < player->getMaxNumChains()) {
							// create new chain
							cout << "Creating new chain\n";
							player->createChain(tradeAreaCard);
							cout << endl << *player << endl << endl;
						}
						else {
							// cards can't be added to the chains, harvest
							chainToHarvest = discardChainMenu(player->getNumChains());
							cout << "Harvesting " << chainToHarvest << endl;
							player->sellChain(chainToHarvest, table->getDiscardPile());
							tradeAreaCard = addToChainIfPossible(player, tradeAreaCard);
						}
					}
				}
				else {
					// discard card
					table->getDiscardPile() += tradeAreaCard;
					tradeAreaCard = NULL;
				}
			}
			
			do {
				player->getHand() += table->getDeck().draw();
				cout << "Hand of " << player->getName() << ": ";
				player->printHand(cout, true);
				cout << endl << endl;
				handCard = player->getHand().play();
				cout << "Card to play : " << *handCard << endl << endl;
				// check if chain ended
				sellMaxedChain(player, table->getDiscardPile());

				// parse chains to add card
				handCard = addToChainIfPossible(player, handCard);
				// check if chain ended TODO check if this is valid
				sellMaxedChain(player, table->getDiscardPile());

				if (handCard != NULL) {
					// card can't be added to existing chain
					cout << "Card " << *handCard << " can't be added to existing chains\n";
					if (player->getNumChains() == player->getMaxNumChains()) {
						// has no empty slots
						// ask player which chain to discard
						chainToHarvest = discardChainMenu(player->getNumChains());
						cout << "chainToHarvest " << chainToHarvest << endl;
						player->sellChain(chainToHarvest, table->getDiscardPile());
					}
					// create chain with card
					cout << "Creating new chain\n";
					player->createChain(handCard);
					cout << endl << *player << endl << endl;
				}

				// show player hand
				cout << endl << *player << endl << endl;

				// check if player wants to continue playing his hand
				cout << endl;
				cout << "Hand of " << player->getName() << ": ";
				player->printHand(cout, true);
				cout << endl;
				playerWantToPlay = playerWantToPlayMenu();
				cout << endl;
			} while (playerWantToPlay);
			
			// give choice to discard a card
			cout << endl;
			iCardToDiscardFromHand = discardCardIndexFromHandMenu(player->getHand());
			cout << endl;
			if (iCardToDiscardFromHand != -1) {
				handCard = player->getHand()[iCardToDiscardFromHand];
				player->getHand().remove(handCard);
				table->getDiscardPile() += handCard;
				handCard = NULL;
				player->printHand(cout, true);
				cout << endl;
			}

			// add 3 cards from deck to trade area
			cout << "Drawing 3 cards from deck to trade area\n";
			for (int i = 0; i < 3; i++) {
				if (table->getDeck().size() > 0) {
					tradeAreaCard = table->getDeck().draw();
					cout << "Drew " << tradeAreaCard->getName() << " From Deck, adding to trade area" << endl;
					table->getTradeArea() += tradeAreaCard;
					tradeAreaCard = NULL;
				}
			}

			// add cards from discard pile to trade area
			cout << "adding cards from discard pile to trade area" << endl << endl;
			while (table->getTradeArea().legal(table->getDiscardPile().top())) {
				cout << table->getDiscardPile() << endl;
				tradeAreaCard = table->getDiscardPile().pickUp();
				table->getTradeArea() += tradeAreaCard;
				tradeAreaCard = NULL;
			}

			// parse trade area
			cout << table->getTradeArea() << endl;
			for (Card* c : table->getTradeArea().getList()) {
				if (chainOrLeaveMenu(c->getName())) {
					// TODO check if you can harvest
					addToChainIfPossible(player, c);
					// check if chain ended TODO check if this is valid
					sellMaxedChain(player, table->getDiscardPile());
				}
			}

			// draws 2 cards
			cout << "drawing 2 cards" << endl;
			for (int i = 0; i < 2; i++) {
				if (table->getDeck().size() > 0) {
					handCard = table->getDeck().draw();
					cout << "Drew " << handCard->getName() << " From Deck, adding to hand" << endl;
					player->getHand() += handCard;
					handCard = NULL;
				}
			}
		}
	}
	// check winner
	Player player1 = table->getPlayer(0);
	Player player2 = table->getPlayer(1);
	cout << "THE GAME IS OVER\n";
	cout << "\tPlayer 1: " << (table->win(player1.getName())? "wins": "loses") << "\n";
	cout << "\tPlayer 2: " << (table->win(player2.getName()) ? "wins" : "loses") << "\n";
}
