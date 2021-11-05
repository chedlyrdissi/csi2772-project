#include "CardFactory.h"
#include "Deck.h"
#include "DiscardPile.h"
#include <iostream>
#include "./card/Black.h"
#include "./card/Blue.h"

using namespace std;

void testDeck() {
	CardFactory cf;
	Deck d(std::cin, &cf);
	Black b;
	Blue bl;
	d.push_back(&b);
	d.push_back(&bl);
	cout << d[0]->getName() << " " << d[1]->getName() << endl;
	cout << d.draw()->getName() << endl;
	cout << d.size() << endl;
}

int main() {
	CardFactory cf;
	DiscardPile d(std::cin, &cf);
	Black b;
	Blue bl;
	d.push_back(&b);
	d.push_back(&bl);
	cout << top() << endl;
	cout << d[0]->getName() << " " << d[1]->getName() << endl;
	cout << pickUp() << endl;
	cout << d.size() << endl;
	cout << d[0]->getName() << endl;
}
