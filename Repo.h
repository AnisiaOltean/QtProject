#pragma once

#include "activitate.h"
#include <vector>
using std::vector;

/*Clasa de exceptii pt. repository*/
class RepoException {
private:
	string errmsg;
public:
	//constructor repoexception
	RepoException(string errMsg) : errmsg{ errMsg } {};
	string getErrmsg() {
		return this->errmsg;
	}
};

class ActivitateRepo {
private:
	vector <Activitate> allActivities;
public:
	//constructor default de copiere
	ActivitateRepo() = default;
	ActivitateRepo(const ActivitateRepo& ot) = delete;

	const Activitate& find(string titlu, string descriere);
	/*
	* Cauta o activitate dupa titlu si descriere
	* @param: titlu, string, titlul activitatii pe care o cautam
	* @param: descriere, string, descrierea activitatii
	* @throws: RepoException() daca activitatea data nu se gaseste in lista
	*/

	bool exista(const Activitate& a);
	/* Verifica daca activitatea exista in lista (cu titlul si descrierea date)
	* @param: a, actiivtate, activitatea cautata
	* @return: bool, true daca se gasete, false altfel
	*/

	virtual void store(const Activitate& a);
	/*
		Adauga activitatea citita in lista
		@throws: RepoException daca activitatea exista deja in lista
	*/

	virtual void delete_by_titlu(const string& titlu);
	/*
	* Sterge din lista activitatile ce au titlul egal cu titlul citit
	* @param: titlu, string, titlul citit de la tastatura
	*/

	virtual void modifica(string titlu, string descriere, string tip, double durata);
	/*
		Cauta activitatea cu titlul si descrierea date si modifica tipul si durata
		activitatii
		@param: titlu, string, titlul activitatii
		@param: descriere, string, descrierea activitatii
		@param: tip, string, noul tip
		@param: durata, double, noua durata
		@throws: RepoException daca activitatea nu exista in lista
	*/

	/*Returneaza lista formata din toate activitatile*/
	const vector <Activitate>& getAll() noexcept {
		return this->allActivities;
	}
};


class RepoFile : public ActivitateRepo {

private:
	string fname;
	void loadfromfile();
	void savetofile();
public:
	RepoFile(string fname) : ActivitateRepo(), fname{ fname }{
		loadfromfile();  //incarcam datele din fisier
	}
	void store(const Activitate& a) override;
	void delete_by_titlu(const string& titlu) override;
	void modifica(string titlu, string descriere, string tip, double durata) override;

};

void testeRepo();




