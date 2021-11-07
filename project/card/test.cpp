#include "Black.h"
#include "Blue.h"
#include "Chili.h"
#include "Garden.h"
#include "Green.h"
#include "Red.h"
#include "Soy.h"
#include "Stink.h"

using namespace std;


void testCard(Card& c, string label) {
	cout << endl << endl << "testing for " << label << endl;
	for (int i = 0; i < 5; i++) {
		cout << "getCardsPerCoin " << c.getCardsPerCoin(i) << endl;
	}
	cout << "getName " << c.getName() << endl;
	cout << c;
	cout << "\ntesting for " << label << endl << endl << endl;
}

int main() {
	Black b;
	testCard(b, "black");
	Blue bl;
	testCard(bl, "blue");
	Chili ch;
	testCard(ch, "Chili");
	Garden g;
	testCard(g, "garden");
	Green G;
	testCard(G, "green");
	Red r;
	testCard(r, "red");
	Soy s;
	testCard(s, "soy");
	Stink st;
	testCard(st, "stink");

	return 0;
}
