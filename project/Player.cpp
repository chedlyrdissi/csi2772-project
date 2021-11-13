#include <iostream>
#include <string>
#include "player.h"
#include "Hand.h"
#include "./card/black.h"
#include "./card/Red.h"
#include "./card/Green.h"
#include "./card/Blue.h"
#include "Table.h"

using namespace std;

int main2() {
	black b;
	Red r;
	Green g;
	Blue bl;
	/*
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
	*/
	Chain<Blue> cb;
	cb += &bl;
	Chain<Red> cr;
	cr += &r;
	cr += &r;
	cr += &r;
	cout << cb << endl;
	cout << cr << endl;
	string name = "player";
	Player p(name);
	p[0] += &b;
	p[0] += &b;
	p[0] += &b;
	p[1] += &r;
	cout << p << endl;
	return 0;
}
