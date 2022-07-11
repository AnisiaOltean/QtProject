#pragma once
#include "activitate.h"
#include "Observer.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

#include <fstream>

using std::vector;


class ListaException {
private:
	string errmsg;
public:
	//constructor repoexception
	ListaException(string errMsg) : errmsg{ errMsg } {};
	string getErrmsg() {
		return this->errmsg;
	}
};

class ListaActivitati{
private:
	vector<Activitate> listaActivitati;
public:
	ListaActivitati() = default; //constructor default

	void adaugaLista(const Activitate& a);
	/*
	Adauga activitatea a in lista de activitati
	@param: a- obiect de tip activitate, actovotatea de adaugat
	return: -
	*/
	void stergeLista(string titlu);
	/*
	* Sterge activitatea cu titlul dat din lista
	*/
	void golesteLista() noexcept;
	/*
	Sterge toate elementele din lista curenta
	*/

	int exista(const Activitate& a);
	//verifica daca activitatea data exista deja in lista si sretunreaza 1 daca 
	//activitatea cautata exista deja in lista, 0 altfel


	int genereazaRandom(vector<Activitate> toate, int cate);
	/*
		Genereaza random obiecte si le adauga in lista de activitati
		@param: toate- lista de activitati existenta (din repo)
		@param: cate- int , cate noi activitati for fi adaugate
		return: -, activitatile vor fi adaugate
	*/

	void saveToFile(string fileName);

	const vector<Activitate>& getAll() noexcept {
		return this->listaActivitati;
	}
};

void testeLista();


