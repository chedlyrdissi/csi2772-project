#include "Chain_Base.h"
#include <vector>
#include <iostream>

class CardFactory {

};

template<typename T>
class Chain: public virtual Chain_Base {
	vector<T*> cards;
public:
	Chain(istream& in, const CardFactory* cf);	
	Chain<T>& operator+=(Card*);
	int sell();
};

template<typename T>
inline Chain<T>::Chain(istream& in, const CardFactory* cf) {

}

template<typename T>
Chain<T>& Chain::operator+=(Card* card) {
	return *this;
}

int Chain<T>::sell() {
	return 0;
}

#pragma once
