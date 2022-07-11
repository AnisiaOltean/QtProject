#include "Repo.h"
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <fstream>

const Activitate& ActivitateRepo::find(string titlu, string descriere) {
	/*for (auto& a : this->allActivities)
	{
		if (a.getTitlu() == titlu && a.getDescriere() == descriere)
			return a;
	}
	throw RepoException("Activitatea data nu exista in lista!\n");*/

	vector<Activitate>::iterator it = std::find_if(allActivities.begin(), allActivities.end(), [=](const Activitate& a) {
		return a.getTitlu() == titlu && a.getDescriere() == descriere;
		});

	if (it != allActivities.end()) return  (*it);
	else throw RepoException("Activitatea data nu exista in lista!\n");
}

bool ActivitateRepo::exista(const Activitate& a) {
	try {
		find(a.getTitlu(), a.getDescriere());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}

void ActivitateRepo::store(const Activitate& a) {
	if (exista(a) == false)
	{
		this->allActivities.push_back(a);
	}
	else throw RepoException("Activitatea data exista deja in lista!\n");
}


void ActivitateRepo::delete_by_titlu(const string& titlu) {
	int i = 0;
	while (i < this->allActivities.size()) {
		if (allActivities[i].getTitlu() == titlu) {
			allActivities.erase(allActivities.begin() + i);
		}
		else i++;
	}
}

void ActivitateRepo::modifica(string titlu, string descriere, string tip, double durata) {
	int i = 0, ok = 0;

	/*while (i < this->allActivities.size()) {
		if (allActivities[i].getTitlu() == titlu && allActivities[i].getDescriere() == descriere) {
			allActivities[i].setTip(tip);
			allActivities[i].setDurata(durata);
			ok = 1;
		}
		i++;
	}*/
	for (auto& a : this->allActivities) {
		if (a.getTitlu() == titlu && a.getDescriere() == descriere) {
			a.setTip(tip);
			a.setDurata(durata);
			ok = 1;
		}
	}
	if (ok == 0) {
		throw RepoException("Activitatea data nu exista in lista!\n");
	}
}

void testAddRepo() {
	ActivitateRepo a;
	Activitate a1{ "Picnic", "Luni 12:00", "Relax", 3.5 };
	a.store(a1);
	assert(a.getAll().size() == 1);

	Activitate a2{ "Lucru", "Luni-Vineri", "Munca", 8 };
	a.store(a2);
	assert(a.getAll().size() == 2);

	assert(a.exista(a1) == true);
	try {
		a.store(a2);
		assert(false);
	}
	catch (RepoException)
	{
		assert(true);
	}
}

void testFindRepo() {
	ActivitateRepo a;
	Activitate a1{ "Picnic", "Luni 12:00", "Relax", 3.5 };
	a.store(a1);
	assert(a.getAll().size() == 1);
	try {
		//Activitate a2{ "Fotbal", "Marti 18:00", "Sport", 2 };
		a.find("Fotbal", "Marti 18:00");
		assert(false);
	}
	catch (RepoException& e)
	{
		//std::cout << e.getErrmsg();
		assert(e.getErrmsg() == "Activitatea data nu exista in lista!\n");
		assert(true);
	}

	Activitate a2{ "Fotbal", "Marti 18:00", "Sport", 2 };
	a.store(a2);
	auto found = a.find("Fotbal", "Marti 18:00");
	assert(found.getTitlu() == "Fotbal");
	assert(found.getDescriere() == "Marti 18:00");
	assert(found.getTip() == "Sport");
	assert(found.getDurata() == 2);
}

void testDeleteRepo() {
	ActivitateRepo a;
	Activitate a1{ "Picnic", "Luni 12:00", "Relax", 3.5 };
	a.store(a1);
	Activitate a2{ "Picnic", "Marti 16:30", "Excursie", 2.1 };
	a.store(a2);
	assert(a.getAll().size() == 2);
	Activitate a3{ "Fotbal", "Marti 16:30", "Sport", 1.5 };
	a.store(a3);
	Activitate a4{ "Tenis", "Miercuri 19:30", "Sport", 1 };
	a.store(a4);
	assert(a.getAll().size() == 4);
	a.delete_by_titlu("Picnic");
	assert(a.getAll().size() == 2);
}


void testModificaRepo() {
	ActivitateRepo a;
	Activitate a1{ "Picnic", "Luni 12:00", "Relax", 3.5 };
	a.store(a1);
	Activitate a2{ "Picnic", "Marti 16:30", "Excursie", 2.1 };
	a.store(a2);
	assert(a.getAll().size() == 2);
	a.modifica("Picnic", "Luni 12:00", "FreeTime", 1.3);
	auto f = a.find("Picnic", "Luni 12:00");
	assert(f.getTip() == "FreeTime");
	assert(f.getDurata() == 1.3);

	try {
		a.modifica("Fotbal", "Joi", "sport", 1.4);
		assert(false);
	}
	catch (RepoException& ve) {
		//std::cout << ve.getErrmsg();
		assert(ve.getErrmsg() == "Activitatea data nu exista in lista!\n");
		assert(true);
	}
}

void RepoFile::loadfromfile() {
	std::ifstream f(fname);
	if (!f.is_open()) throw RepoException("Fisierul nu poate fi deschis!\n");
	string titlu, desc, tip;
	double durata;
	while (!f.eof()) {
		f >> titlu;
		if (f.eof()) break;
		f >> desc;
		f >> tip;
		f >> durata;

		Activitate a{ titlu.c_str(), desc.c_str(), tip.c_str(), durata };
		ActivitateRepo::store(a);
	}
	f.close();
}

void RepoFile::savetofile() {
	std::ofstream g(fname);
	if (!g.is_open()) throw RepoException("Fisierul nu poate fi deschis!\n");
	for (auto& a : getAll()) {
		g << a.getTitlu();
		g << std::endl;
		g << a.getDescriere();
		g << std::endl;
		g << a.getTip();
		g << std::endl;
		g << a.getDurata();
		g << std::endl;
	}
	g.close();
}

void RepoFile::store(const Activitate& a) {
	ActivitateRepo::store(a);
	savetofile();
}

void RepoFile::delete_by_titlu(const string& titlu) {
	ActivitateRepo::delete_by_titlu(titlu);
	savetofile();
}

void RepoFile::modifica(string titlu, string descriere, string tip, double durata) {
	ActivitateRepo::modifica(titlu, descriere, tip, durata);
	savetofile();
}

void testgetallfile() {
	std::ofstream out;
	out.open("testact.txt", std::ofstream::out | std::ofstream::trunc);
	//out << "Hello!";
	out.close();//creez un fisier gol
	RepoFile repoF{ "test.txt" };
	repoF.store(Activitate{ "Fotbal", "Luni", "sport", 2.4 });
	repoF.store(Activitate{ "Tenis", "Marti", "sport", 2.1 });
	repoF.store(Activitate{ "Fotbal", "Vineri", "antrenament", 2 });
	repoF.store(Activitate{ "Balet", "Sambata", "concert", 5.1 });
	assert(repoF.getAll().size() == 4);
	RepoFile repoF2{ "testact.txt" };
	repoF2.store(Activitate{ "Tenis", "Luni", "sport", 2.3 });
	assert(repoF2.getAll().size() == 1);
	repoF.delete_by_titlu("Fotbal");
	assert(repoF.getAll().size() == 2);
	repoF.modifica("Tenis", "Marti", "antrenament", 5.2);
	auto found = repoF.find("Tenis", "Marti");
	assert(found.getTip() == "antrenament");
	repoF.delete_by_titlu("Tenis");
	repoF.delete_by_titlu("Balet");
	assert(repoF.getAll().size() == 0);
}

void testeRepo() {
	testAddRepo();
	testFindRepo();
	testDeleteRepo();
	testModificaRepo();
	testgetallfile();
}


