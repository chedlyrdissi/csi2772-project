#include <iostream>
#include <string>
#include "player.h"
#include "Hand.h"
#include "./card/Black.h"
#include "./card/Red.h"
#include "./card/Green.h"
#include "./card/Blue.h"

using namespace std;

int main() {
	Black b;
	Red r;
	Green g;
	Blue bl;
	Hand h(std::cin, NULL);
	h += &b;
	cout << h << endl;
	h += &b;
	h += &bl;
	h += &r;
	h += &g;
	h += &bl;
	h += &b;
	h += &r;
	cout << h << endl;
	cout << "play " << *(h.play()) << endl;
	cout << h << endl;
	cout << "top " << *(h.top()) << endl;
	cout << h << endl;
	string name = "player";
	Player p(name);
	cout << p << endl;

	/*
	for (int i = 0; i < 8; i++) {
		cout << *(h[i]) << " ";
	}
	*/
}
