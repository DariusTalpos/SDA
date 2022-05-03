#include "Iterator.h"
#include "DO.h"

#include <exception>
using namespace std;

Iterator::Iterator(const DO& d) : dict(d) {
	//Theta(1)
	pozitie = dict.primOcupat;
}

void Iterator::prim() {
	//Theta(1)
	pozitie = dict.primOcupat;
}

void Iterator::urmator() {
	//Theta(1)
	if (!valid())
		throw exception();
	pozitie=dict.urmator[pozitie];
}

bool Iterator::valid() const {
	//Theta(1)
	if (pozitie >= 0)
		return true;
	return false;
}

TElem Iterator::element() const {
	//Theta(1)
	if (!valid())
		throw exception();
	return dict.elemente[pozitie];
}


