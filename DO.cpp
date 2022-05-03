#include "Iterator.h"

#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;


void DO::redimensionare()
{
	//Theta(capacitate)
	int c = capacitate;
	capacitate *= 2;
	TElem* nElemente = new TElem[capacitate];
	int* nUrmator = new int[capacitate];
	int i = primOcupat;

	while (i != -1)
	{
		nUrmator[i] = urmator[i];
		nElemente[i] = elemente[i];
		i = urmator[i];
	}

	int prevUrm = 0;

	delete[] elemente;
	delete[] urmator;

	urmator = nUrmator;
	elemente = nElemente;

	for (int i = c; i < capacitate; i++)
		urmator[i] = i + 1;

	urmator[capacitate - 1] = -1;
	neocupat = c;

}

DO::DO(Relatie r) {
	//Theta(10)
	rel = r;
	lungime = 0;
	capacitate = 10;

	neocupat = 0;
	primOcupat = -1;

	elemente = new TElem[capacitate];
	urmator = new int[capacitate];
	for (int i = 0; i <= capacitate - 1; i++)
	{
		urmator[i] = i + 1;
	}
	urmator[capacitate - 1] = -1;

}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	//Theta(?)
	if (lungime == capacitate)
		redimensionare();

	TElem e = make_pair(c, v);
	if (primOcupat == -1 || rel(c, elemente[primOcupat].first))
	{
		if(primOcupat!=-1)
			if (elemente[primOcupat].first == c)
			{
				TValoare val = elemente[primOcupat].second;
				elemente[primOcupat].second = v;
				return val;
			}
		int neo = neocupat;
		neocupat = urmator[neocupat];
		elemente[neo] = e;
		urmator[neo] = primOcupat;
		primOcupat = neo;
		lungime++;
	}
	else
	{
		int poz = primOcupat, precedent=0;
		while (urmator[poz] != -1 && !rel(c, elemente[poz].first))
		{
			precedent = poz;
			poz = urmator[poz];
		}
		if (elemente[poz].first == c)
		{
			TValoare val = elemente[poz].second;
			elemente[poz].second = v;
			return val;
		}
		if (rel(c, elemente[poz].first))
		{
			int neo = neocupat;
			neocupat = urmator[neocupat];
			elemente[neo] = e;
			int intrerupere = urmator[precedent];
			urmator[precedent] = neo;
			urmator[neo] = intrerupere;
		}
		else
		{
			int neo = neocupat;
			neocupat = urmator[neocupat];
			elemente[neo] = e;
			int intrerupere = urmator[poz];
			urmator[poz] = neo;
			urmator[neo] = intrerupere;
		}
		lungime++;
	}
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	//O(lungime)
	int poz = primOcupat;
	while (poz != -1)
	{
		if (elemente[poz].first == c)
			return elemente[poz].second;
		poz = urmator[poz];
	}
	return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	//O(lungime)
	int poz = primOcupat;
	while (poz != -1)
	{
		if (elemente[poz].first == c)
		{
			int val = elemente[poz].second;

			if (poz == primOcupat)
			{
				primOcupat = urmator[primOcupat];
				lungime--;
				return val;
			}
			else
			{
				int precedent = primOcupat;
				while (urmator[precedent] != poz)
					precedent = urmator[precedent];
				urmator[precedent] = urmator[poz];
				urmator[poz] = neocupat;
				neocupat = poz;
				lungime--;
				return val;
			}
		}
		poz = urmator[poz];
	}
	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	//Theta(1)
	return lungime;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	//Theta(1)
	if (lungime != 0)
		return false;
	return true;
}

Iterator DO::iterator() const {
	//Theta(1)
	return  Iterator(*this);
}

DO::~DO() {
	//Theta(1)
	delete[] elemente;
	delete[] urmator;
}