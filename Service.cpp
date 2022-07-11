#include "Service.h"
#include <assert.h>
#include <iostream>
#include <functional>
#include <algorithm>

void ActivitateService::addActivitate(string titlu, string descriere, string tip, double durata) {
	Activitate a{ titlu, descriere, tip, durata };
	val.valideaza(a);
	repo.store(a);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, a));
}

void ActivitateService::deleteByTitle(string titlu) {
	vector<Activitate>toDelete;  //retinem in lista activitatile cu titlul citit de la tasattura
	for (const auto& a : this->getAllsrv()) {
		if (a.getTitlu() == titlu)
			toDelete.push_back(a);
	}
	repo.delete_by_titlu(titlu);
	if (!toDelete.empty())
	{
		//for (const auto& a : toDelete)
		undoActions.push_back(std::make_unique<UndoSterge>(repo, toDelete));
	}
}

void ActivitateService::ModificaSrv(string titlu, string descriere, string tip, double durata) {
	Activitate a = repo.find(titlu, descriere);  //retinem actiivtatea veche (inainte de modificare)
	repo.modifica(titlu, descriere, tip, durata);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, a));
}

const Activitate& ActivitateService::found(const string& titlu, const string& descriere) {
	return repo.find(titlu, descriere);
}

void ActivitateService::undo() {
	if (undoActions.empty()) {
		throw RepoException("Nu se mai poate face undo! \n");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

vector<Activitate> ActivitateService::filtreaza(function<bool(const Activitate&)> fct) {
	vector <Activitate> rez;
	for (const auto& a : repo.getAll()) {
		if (fct(a)) {
			rez.push_back(a);
		}
	}
	return rez;
}

vector <Activitate> ActivitateService::filtrareDescriere(const string& descriere) {
	/*return filtreaza([descriere](const Activitate& a) {
		return a.getDescriere() == descriere; });*/
	const vector<Activitate>& all = getAllsrv();
	vector<Activitate>filtered;
	std::copy_if(all.begin(), all.end(), back_inserter(filtered), [=](const Activitate& a) {
		return a.getDescriere() == descriere;
		});
	return filtered;
}

vector <Activitate> ActivitateService::filtrareTip(const string& tip) {
	//return filtreaza([tip](const Activitate& a) {return a.getTip() == tip; });
	const vector<Activitate>& all = getAllsrv();
	vector<Activitate> filtered;
	std::copy_if(all.begin(), all.end(), back_inserter(filtered), [=](const Activitate& a) {
		return a.getTip() == tip;
		});
	return filtered;
}


vector<Activitate> ActivitateService::generalSort(bool (*cmpF)(const Activitate&, const Activitate&)) {
	vector <Activitate> v{ repo.getAll() }; //copie lista 
	for (int i = 0; i < v.size() - 1; i++) {
		for (int j = i; j < v.size(); j++) {
			if (cmpF(v[i], v[j]) == false)
			{
				Activitate aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

vector <Activitate> ActivitateService::sorteazaTitlu() {
	//return generalSort(cmpTitlu);
	vector<Activitate>sorted = { repo.getAll() };
	sort(sorted.begin(), sorted.end(), cmpTitlu);
	return sorted;
}

vector <Activitate> ActivitateService::sorteazaDescriere() {
	//return generalSort(cmpDescriere);
	vector<Activitate>sorted = { repo.getAll() };
	sort(sorted.begin(), sorted.end(), cmpDescriere);
	return sorted;
}

vector <Activitate> ActivitateService::sorteazaTipDurata() {
	/*return generalSort([](const Activitate& a1, const Activitate& a2) {
		if (a1.getTip() == a2.getTip())
		{
			return a1.getDurata() < a2.getDurata();
		}
		return a1.getTip() < a2.getTip();
		});*/
	vector<Activitate>sorted = { repo.getAll() };
	sort(sorted.begin(), sorted.end(), cmpTipDurata);
	return sorted;
}


void ActivitateService::adaugaLista(string titlu, string descriere) {
	const auto& a = repo.find(titlu, descriere);
	ListaCurenta.adaugaLista(a);
	//std::cout << "Exista" << getListaCurenta().size() << "elemente \n";
	notify();
}
void ActivitateService::stergeTitlu(string titlu) {
	ListaCurenta.stergeLista(titlu);
	notify();
}

int ActivitateService::addRandom(int cate) {
	int d = ListaCurenta.genereazaRandom(this->getAllsrv(), cate);
	//return ListaCurenta.getAll().size();
	notify();
	return d;
}


void ActivitateService::clearLista() noexcept {
	ListaCurenta.golesteLista();
	notify();
}

void ActivitateService::exportFile(string fname) {
	try {
		ListaCurenta.saveToFile(fname);
	}
	catch (ListaException& ve) {
		assert(ve.getErrmsg() == "Fisierul nu poate fi deschis! \n");
	}
}
unordered_map<string, DTO> ActivitateService::getTip(string tip) {
	int ct = 0;
	unordered_map<string, DTO>set;
	for (const Activitate& a : this->getAllsrv()) {
		if (a.getTip() == tip) {
			ct++;
		}
	}
	set[tip] = DTO(tip, ct);
	return set;
}


void testUndo() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };
	s.addActivitate("Gatit", "Vineri 20:00", "sport", 4);
	s.addActivitate("Lucru", "Luni-Vineri", "sport", 8);
	s.addActivitate("Tenis", "Joi", "antrenament", 8);
	assert(s.getAllsrv().size() == 3);
	s.undo();
	assert(s.getAllsrv().size() == 2);
	s.undo();
	assert(s.getAllsrv().size() == 1);
	s.undo();
	assert(s.getAllsrv().size() == 0);
	try {
		s.undo();
		assert(false);
	}
	catch (RepoException& ve) {
		//std::cout << ve.getErrmsg();
		assert(ve.getErrmsg() == "Nu se mai poate face undo! \n");
		assert(true);
	}

	s.addActivitate("Gatit", "Vineri 20:00", "sport", 4);
	s.addActivitate("Gatit", "Luni-Vineri", "sport", 8);
	assert(s.getAllsrv().size() == 2);
	s.deleteByTitle("Gatit");
	assert(s.getAllsrv().size() == 0);
	s.undo();
	//for (const auto& a : s.getAllsrv())
		//std::cout << a.getTitlu() << " " << a.getDescriere() << "\n";
	assert(s.getAllsrv().size() == 2);

	s.ModificaSrv("Gatit", "Luni-Vineri", "hobby", 6.2);
	assert(s.getAllsrv()[1].getTip() == "hobby");
	s.undo();
	assert(s.getAllsrv()[1].getTip() == "sport");
	assert(s.getAllsrv()[1].getDurata() == 8);
}

void testgetTip() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };
	s.addActivitate("Gatit", "Vineri 20:00", "sport", 4);
	s.addActivitate("Lucru", "Luni-Vineri", "sport", 8);
	s.addActivitate("Tenis", "Joi", "antrenament", 8);
	unordered_map<string, DTO>rez;
	assert(rez.empty() == true);
	rez = s.getTip("sport");
	assert(rez["sport"].getNr() == 2);
	assert(rez.empty() == false);
	//std::cout << rez["sport"].getNr();
}

void testExport() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };
	s.addActivitate("Gatit", "Vineri 20:00", "sport", 4);
	s.addActivitate("Lucru", "Luni-Vineri", "sport", 8);
	s.addActivitate("Tenis", "Joi", "antrenament", 8);

	s.adaugaLista("Gatit", "Vineri 20:00");
	s.adaugaLista("Lucru", "Luni-Vineri");
	s.adaugaLista("Tenis", "Joi");

	s.exportFile("test1.html");
}

void testStergeL() {
	ActivitateRepo testrepo;
	ActivitateValidator testval;
	ActivitateService tests{ testrepo, testval };
	tests.addActivitate("A1", "B1", "C1", 1.1);
	tests.addActivitate("A3", "B3", "C3", 1.4);
	tests.addActivitate("A2", "B2", "C2", 2);
	tests.addActivitate("A6", "B6", "C6", 2.1);
	tests.addActivitate("A5", "B5", "C5", 10.1);
	tests.addActivitate("A4", "B4", "C4", 0.1);
	tests.addActivitate("A7", "B7", "C7", 2.3);
	tests.addActivitate("A7", "B3", "C3", 1);

	tests.addRandom(4);
	assert(tests.getListaCurenta().size() == 4);
	tests.clearLista();
	assert(tests.getListaCurenta().size() == 0);

	tests.adaugaLista("A1", "B1");
	assert(tests.getListaCurenta().size() == 1);
	tests.stergeTitlu("A1");
	assert(tests.getListaCurenta().size() == 0);
}
void testAddService() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };

	try {
		s.addActivitate("Fotbal", "Marti 18:00", "Sport", 2.1);
		assert(true);
	}
	catch (ValidationException) {
		assert(false);
	}
	s.addActivitate("Gatit", "Vineri 20:00", "Timp cu familia", 4);
	s.addActivitate("Lucru", "Luni-Vineri", "Munca", 8);
	assert(s.getAllsrv().size() == 3);

	try {
		s.addActivitate("", "Marti 18:00", "Sport", 2.1);
		assert(false);
	}
	catch (ValidationException& ve) {
		//std::cout << ve.getErrMsg();
		assert(ve.getErrMsg() == "Titlul nu poate fi vid!\n");
		assert(true);
	}
	try {
		s.addActivitate("Fotbal", "", "Sport", 2.1);
		assert(false);
	}
	catch (ValidationException& ve) {
		//std::cout << ve.getErrMsg();
		assert(ve.getErrMsg() == "Descrierea nu poate fi vida!\n");
		assert(true);
	}

	try {
		s.addActivitate("Fotbal", "Luni 16", "", 2.1);
		assert(false);
	}
	catch (ValidationException& ve) {
		//std::cout << ve.getErrMsg();
		assert(ve.getErrMsg() == "Tipul nu poate fi vid!\n");
		assert(true);
	}

	try {
		s.addActivitate("Fotbal", "Luni 16", "Sport", -2.1);
		assert(false);
	}
	catch (ValidationException& ve) {
		//std::cout << ve.getErrMsg();
		assert(ve.getErrMsg() == "Durata trebuie sa fie pozitiva!\n");
		assert(true);
	}

	try {
		s.addActivitate("Fotbal", "Luni 16", "Sport", 2.6);
		assert(false);
	}
	catch (ValidationException& ve) {
		//std::cout << ve.getErrMsg();
		assert(ve.getErrMsg() == "Formatul duratei este invalid!\n");
		assert(true);
	}

	try {
		s.addActivitate("Fotbal", "Marti 18:00", "Sport", 2.1);
		assert(false);
	}
	catch (RepoException& ve) {
		//std::cout << ve.getErrmsg();
		assert(ve.getErrmsg() == "Activitatea data exista deja in lista!\n");
		assert(true);
	}

}

void testDeleteService() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };
	s.addActivitate("Picnic", "Luni 12:00", "Relax", 3.5);
	s.addActivitate("Picnic", "Marti 12:00", "Excursie", 2);
	s.addActivitate("Fotbal", "Luni 18:00", "Sport", 2);
	s.addActivitate("Picnic", "Joi", "Relax", 1);
	assert(s.getAllsrv().size() == 4);
	s.deleteByTitle("Picnic");
	assert(s.getAllsrv().size() == 1);
}

void testModificaSrv() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };
	s.addActivitate("Picnic", "Luni 12:00", "Relax", 3.5);
	s.addActivitate("Picnic", "Marti 12:00", "Excursie", 2);
	s.addActivitate("Fotbal", "Luni 18:00", "Sport", 2);
	s.addActivitate("Picnic", "Joi", "Relax", 1);
	s.ModificaSrv("Fotbal", "Luni 18:00", "Miscare", 1.2);
	auto l = s.getAllsrv();
	assert(l[2].getTip() == "Miscare");
	assert(l[2].getDurata() == 1.2);

	try {
		s.ModificaSrv("Tenis", "Luni", "Sport", 2.3);
		assert(false);
	}
	catch (RepoException& ve) {
		//std::cout << ve.getErrmsg();
		assert(ve.getErrmsg() == "Activitatea data nu exista in lista!\n");
		assert(true);
	}
}

void testFound() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };
	s.addActivitate("Picnic", "Luni 12:00", "Relax", 3.5);
	s.addActivitate("Picnic", "Marti 12:00", "Excursie", 2);
	s.addActivitate("Fotbal", "Luni 18:00", "Sport", 2);
	auto f = s.found("Fotbal", "Luni 18:00");
	assert(f.getTitlu() == "Fotbal");
	assert(f.getDescriere() == "Luni 18:00");

	try {
		auto f2 = s.found("Tenis", "Maine");
		assert(false);
	}
	catch (RepoException& ve) {
		//std::cout << ve.getErrmsg();
		assert(ve.getErrmsg() == "Activitatea data nu exista in lista!\n");
		assert(true);
	}
}

void testFiltrareDesc() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };
	s.addActivitate("Picnic", "Luni 12:00", "Relax", 3.5);
	s.addActivitate("Picnic", "Marti 12:00", "Excursie", 2);
	s.addActivitate("Fotbal", "Luni 12:00", "Sport", 2);
	auto rez = s.filtrareDescriere("Luni 12:00");
	assert(rez.size() == 2);
	assert(rez[0].getTitlu() == "Picnic");
	assert(rez[1].getTitlu() == "Fotbal");
}

void testFiltrareTip() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };
	s.addActivitate("Picnic", "Luni 12:00", "Relax", 3.5);
	s.addActivitate("Picnic", "Marti 12:00", "Excursie", 2);
	s.addActivitate("Fotbal", "Luni 12:00", "Relax", 2);
	auto rez = s.filtrareTip("Relax");
	assert(rez.size() == 2);
	assert(rez[0].getTitlu() == "Picnic");
	assert(rez[1].getTitlu() == "Fotbal");
}

void testSortTitlu() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };
	s.addActivitate("Picnic", "Luni 12:00", "Relax", 3.5);
	s.addActivitate("Gatit", "Marti 12:00", "Excursie", 2);
	s.addActivitate("Fotbal", "Luni 12:00", "Relax", 2);
	auto rez = s.sorteazaTitlu();
	assert(rez.size() == 3);
	assert(rez[0].getTitlu() == "Fotbal");
	assert(rez[1].getTitlu() == "Gatit");
	assert(rez[2].getTitlu() == "Picnic");
}

void testSortDesc() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };
	s.addActivitate("Picnic", "Luni 12:00", "Relax", 3.5);
	s.addActivitate("Gatit", "Marti 12:00", "Excursie", 2);
	s.addActivitate("Fotbal", "Joi 11:00", "Relax", 2);
	auto f = s.sorteazaDescriere();
	assert(f.size() == 3);
	assert(f[0].getTitlu() == "Fotbal");
	assert(f[1].getTitlu() == "Picnic");
	assert(f[2].getTitlu() == "Gatit");
}

void testSortTipDurata() {
	ActivitateRepo repo;
	ActivitateValidator val;
	ActivitateService s{ repo, val };
	s.addActivitate("Picnic", "Luni 12:00", "relax", 3.5);
	s.addActivitate("Gatit", "Marti 12:00", "excursie", 2);
	s.addActivitate("Fotbal", "Joi 11:00", "sport", 2.1);
	s.addActivitate("Tenis", "Joi 11:00", "sport", 2);
	auto filt = s.sorteazaTipDurata();
	assert(filt.size() == 4);
	assert(filt[0].getTitlu() == "Gatit");
	assert(filt[1].getTitlu() == "Picnic");
	assert(filt[2].getTitlu() == "Tenis");
	assert(filt[3].getTitlu() == "Fotbal");
}


void testeListaNoua() {
	ActivitateRepo testrepo;
	ActivitateValidator testval;
	ActivitateService tests{ testrepo, testval };
	tests.addActivitate("A1", "B1", "C1", 1.1);
	tests.addActivitate("A3", "B3", "C3", 1.4);
	tests.addActivitate("A2", "B2", "C2", 2);
	tests.addActivitate("A6", "B6", "C6", 2.1);
	tests.addActivitate("A5", "B5", "C5", 10.1);
	tests.addActivitate("A4", "B4", "C4", 0.1);
	tests.addActivitate("A7", "B7", "C7", 2.3);
	tests.addActivitate("A7", "B3", "C3", 1);

	tests.addRandom(4);
	assert(tests.getListaCurenta().size() == 4);
	tests.clearLista();
	assert(tests.getListaCurenta().size() == 0);

	tests.adaugaLista("A1", "B1");
	assert(tests.getListaCurenta().size() == 1);

	try {
		tests.adaugaLista("A6", "B5");
		assert(false);
	}
	catch (RepoException& v) {
		//std::cout << v.getErrmsg();
		assert(v.getErrmsg() == "Activitatea data nu exista in lista!\n");
		assert(true);
	}
}

void testeService() {
	testAddService();
	testDeleteService();
	testModificaSrv();
	testFound();
	testFiltrareDesc();
	testFiltrareTip();
	testSortTitlu();
	testSortDesc();
	testSortTipDurata();
	testeListaNoua();
	testgetTip();
	testExport();
	testUndo();
}