#pragma once
#include "Observer.h"
#include "Repo.h"
#include "validators.h"
#include <functional>
#include "ListaActivitati.h"
#include <unordered_map>
#include "DTO.h"
#include "Undo.h"

using std::function;
using std::unordered_map;
using std::unique_ptr;


class ActivitateService: public Observable{
private:
	ActivitateRepo& repo;
	ActivitateValidator& val;

	ListaActivitati ListaCurenta;

	vector<unique_ptr<ActiuneUndo>> undoActions;

	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar animalele care trec de filtru (fct(pet)==true)
	*/
	vector<Activitate> filtreaza(function<bool(const Activitate&)> fct);

	/*
	 Functie de sortare generala
	 maiMareF - functie care compara 2 Pet, verifica daca are loc relatia mai mare
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Pet)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	vector<Activitate> generalSort(bool (*cmpF)(const Activitate&, const Activitate&));
public:
	//constructor service
	ActivitateService(ActivitateRepo& repo, ActivitateValidator& val) : repo{ repo }, val{ val } {}

	ActivitateService(const ActivitateService& ot) = delete;

	void addActivitate(string titlu, string descriere, string tip, double durata);
	/*
		Valideaza datele citite de la tastatura si adauga activitatea in lista de activitati
		@param: titlu, string, titlul citit
		@param: descriere, string, descrierea citita
		@param: tip, string, tipul citit
		@param: durata, double, durata citita
		@throws: ValidationException daca apar erori in validarea activitatii
	*/

	void deleteByTitle(string titlu);
	/*
	* Sterge elementele din lista ce au titlul egal cu titlul citit
	* @param: titlu, string, titlul citit
	*/
	void ModificaSrv(string titlu, string descriere, string tip, double durata);
	/*
		Cauta activitatea cu titlul si descrierea date si modifica tipul si durata
		activitatii
		@param: titlu, string, titlul activitatii
		@param: descriere, string, descrierea activitatii
		@param: tip, string, noul tip
		@param: durata, double, noua durata
		@throws: RepoException daca activitatea nu exista in lista
	*/

	const Activitate& found(const string& titlu, const string& descriere);
	/*
		Returneaza activitatea ce are titlul si descrierea date
		@param: titlu, string, titlul citit
		@param: descriere, string, descrierea citita
		@throws: RepoException daca activitatea nu este gasita
	*/

	vector <Activitate> filtrareDescriere(const string& descriere);
	/*
		Returneaza lista formata din activitatile ce au descrierea egala cu descrierea data
		@param: descriere, string, descrierea data
	*/
	vector <Activitate> filtrareTip(const string& tip);
	/*
		Returneaza lista formata din activitatile ce au tipul egal cu tipul dat
		@param: tip, string, tipul dat
	*/

	vector <Activitate> sorteazaTitlu();
	/*
		Returneaza vectorul sortat dupa titlul actiivtatilor
	*/

	vector <Activitate> sorteazaDescriere();
	/*
		Returneaza vectorul sortat dupa descrierea actiivtatilor
	*/

	vector <Activitate> sorteazaTipDurata();
	/*
	* Returneaza vectorul sortat dupa tipul si durata activitatilor
	*/

	const vector<Activitate>& getAllsrv() noexcept {
		return this->repo.getAll();
	}

	void adaugaLista(string titlu, string descriere);
	/*
	Adauga in lista activitatea cu titlul si descrierea citite de la tastatura
	*/

	void clearLista() noexcept;
	/*
	Sterge toate activitatile din lista
	*/

	int addRandom(int cate);
	/*
	Se adauga "cate" activitati generate aleator in noua lista
	return: int, cate activitati noi au fost adaugate
	*/

	void undo();
	/*
		Se efectueaza undo ultimei operatii efectuate
		@throws: RepoException daca nu se mai poate face undo
	*/
	unordered_map<string, DTO> getTip(string tip);
	//returneaza un dictionar neordonat pentru tipul dat

	void exportFile(string fname);

	void stergeTitlu(string titlu);
	/*
	* Sterge activitatile din lista cu titlul dat
	*/

	const vector<Activitate>& getListaCurenta() {
		return ListaCurenta.getAll();
	}
};

void testeService();
//void testAddService();



