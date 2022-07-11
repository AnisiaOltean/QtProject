
#include "ListaActivitati.h"
#include "validators.h"
#include <assert.h>

int ListaActivitati::exista(const Activitate& a) {
	for (const Activitate& b : this->getAll()) {
		if (b.getTitlu() == a.getTitlu() && b.getDescriere() == a.getDescriere())
			return 1;
	}
	return 0;
}


void ListaActivitati::adaugaLista(const Activitate& a) {
	if (exista(a) == 0)
		this->listaActivitati.push_back(a);
	else throw ListaException("Activitatea exista deja in lista!\n");
	//notify();
}

void ListaActivitati::stergeLista(string titlu) {
	int i = 0;
	while (i < listaActivitati.size()) {
		if (listaActivitati.at(i).getTitlu() == titlu) {
			listaActivitati.erase(listaActivitati.begin() + i);
		}
		else i++;
	}
}

void ListaActivitati::golesteLista() noexcept {
	this->listaActivitati.clear();
	//notify();
}

int ListaActivitati::genereazaRandom(vector<Activitate> toate, int cate) {
	shuffle(toate.begin(), toate.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	int added = 0;
	while (listaActivitati.size() < cate && toate.size() > 0) {
		if (exista(toate.back()) == 0)
		{
			added++;
			listaActivitati.push_back(toate.back());
			toate.pop_back();
		}
		else
			toate.pop_back();
	}
	//notify();
	return added;
}

void ListaActivitati::saveToFile(string fileName) {
	std::ofstream fout(fileName);
	if (!fout.is_open()) {
		throw ListaException("Fisierul nu poate fi deschis! \n");
	}
	fout << "<!DOCTYPE HTML>" << "\n";
	fout << "<html>" << "\n";
	fout << "<head>" << "\n";
	fout << "<title> Lista de activitati </title>" << "\n";
	fout << "</head> " << "\n";
	fout << "<body style=\"background-color: #bee3e1;\">" << "\n";
	fout << "<h1 style=\"text-align: center; color: red; font-family: Helvetica; font-size: 40px;\">" << "\n";
	fout << "Elementele din lista sunt : " << "\n";
	fout << "</h1>" << "\n";
	fout << "<p style=\"font-family: verdana; font-size: 24px;\">" << "\n";
	fout << "<table style=\"width: 100%;\">" << "\n";
	fout << "<th style=\"width: 25%; font-family: verdana; font-size: 24px; color: green;\"> Titlu </th>" << "\n";
	fout << "<th style=\"width: 25%;font-family: verdana; font-size: 24px;color: green;\"> Descriere </th>" << "\n";
	fout << "<th style=\"width: 25%;font-family: verdana; font-size: 24px;color: green;\"> Tip </th>" << "\n";
	fout << "<th style=\"width: 25%;font-family: verdana; font-size: 24px;color: green;\"> Durata </th>" << "\n";
	//fout << "<br>";
	for (const auto& a : this->getAll()) {
		fout << "<tr>" << "\n";
		fout << "<td style=\"text-align: center; font-family: verdana; font-size: 20px;\">" << a.getTitlu() << "\n";
		fout << "</td>" << "\n";
		fout << "<td style=\"text-align: center;font-family: verdana; font-size: 20px;\"> " << a.getDescriere() << "\n";
		fout << "</td>" << "\n";
		fout << "<td style=\"text-align: center;font-family: verdana; font-size: 20px;\">" << a.getTip() << "\n";
		fout << "</td>" << "\n";
		fout << "<td style=\"text-align: center;font-family: verdana; font-size: 20px;\">" << a.getDurata() << "\n";
		fout << "</td>" << "\n";
		fout << "</tr>" << "\n";
	}
	fout << "</p>" << "\n";
	fout << "</body>" << "\n";
	//fout << "hehehe";
	fout << "</html>" << "\n";
	fout.close();
}


void testExista() {
	ListaActivitati l;
	assert(l.getAll().size() == 0);
	Activitate a{ "Tenis", "Luni", "sport", 2.3 };
	l.adaugaLista(a);
	Activitate a1{ "Fotbal", "Luni", "examen", 2.3 };
	//l.adaugaLista(a1);
	assert(l.exista(a) == 1);
	assert(l.exista(a1) == 0);
}

void testAdaugaGolesteLista() {
	ListaActivitati l;
	assert(l.getAll().size() == 0);
	Activitate a{ "Tenis", "Luni", "sport", 2.3 };
	l.adaugaLista(a);
	assert(l.getAll().size() == 1);
	try {
		l.adaugaLista(a);
		assert(false);
	}
	catch (ListaException& e) {
		//std::cout << e.getErrmsg();
		assert(e.getErrmsg() == "Activitatea exista deja in lista!\n");
		assert(true);
	}
	l.golesteLista();
	assert(l.getAll().size() == 0);
}

void testSaveFile() {
	ListaActivitati l;
	assert(l.getAll().size() == 0);
	Activitate a{ "Tenis", "Luni", "sport", 2.3 };
	l.adaugaLista(a);
	Activitate a1{ "Fotbal", "Miercuri", "sport", 3.1 };
	l.adaugaLista(a1);
	Activitate a2{ "Balet", "Joi", "antrenament", 4 };
	l.adaugaLista(a2);
	assert(l.getAll().size() == 3);
	string fname = "test.html";
	try {
		l.saveToFile(fname);
		assert(true);
	}
	catch (ListaException& ve) {
		//std::cout << ve.getErrmsg();
		assert(ve.getErrmsg() == "Fisierul nu poate fi deschis! \n");
		assert(false);
	}
}

void testSterge() {
	ListaActivitati l;
	assert(l.getAll().size() == 0);
	Activitate a{ "Tenis", "Luni", "sport", 2.3 };
	l.adaugaLista(a);
	assert(l.getAll().size() == 1);
	l.stergeLista("Tenis");
	assert(l.getAll().size() == 0);
}
void testeLista() {
	testExista();
	testAdaugaGolesteLista();
	testSaveFile();
	testSterge();
}