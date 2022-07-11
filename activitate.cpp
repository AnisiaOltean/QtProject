#include "activitate.h"
#include <assert.h>

string Activitate::getTitlu() const  noexcept {
	return this->titlu;
}

string Activitate::getDescriere() const noexcept {
	return this->descriere;

}

string Activitate::getTip() const noexcept {
	return this->tip;
}

double Activitate::getDurata() const noexcept {
	return this->durata;
}

void Activitate::setTitlu(string TitluNou) {
	this->titlu = TitluNou;
}

void Activitate::setDescriere(string DescrNoua) {
	this->descriere = DescrNoua;
}

void Activitate::setTip(string TipNou) {
	this->tip = TipNou;
}

void Activitate::setDurata(double DurataNoua) noexcept {
	this->durata = DurataNoua;
}

void testGetSet() {
	Activitate a1{ "Film", "Spiderman 3", "Divertisment", 3.2 };
	assert(a1.getTitlu() == "Film");
	assert(a1.getDescriere() == "Spiderman 3");
	assert(a1.getTip() == "Divertisment");
	assert(a1.getDurata() == 3.2);

	a1.setTitlu("Picnic");
	a1.setDescriere("Iarba verde");
	a1.setTip("Vacanta");
	a1.setDurata(3);

	assert(a1.getTitlu() == "Picnic");
	assert(a1.getDescriere() == "Iarba verde");
	assert(a1.getTip() == "Vacanta");
	assert(a1.getDurata() == 3);

}

bool cmpTitlu(const Activitate& a1, const Activitate& a2) noexcept {
	return a1.getTitlu() < a2.getTitlu();
}

void testCmpTitlu() {
	Activitate a1{ "Film", "Spiderman 3", "Divertisment", 3.2 };
	Activitate a2{ "Tenis", "Spiderman 3", "Divertisment", 3.2 };
	assert(cmpTitlu(a1, a2) == true);
	assert(cmpTitlu(a2, a1) == false);
}

bool cmpDescriere(const Activitate& a1, const Activitate& a2) noexcept {
	return a1.getDescriere() < a2.getDescriere();
}

void testCmpDescriere() {
	Activitate a1{ "Film", "Hobby", "Divertisment", 3.2 };
	Activitate a2{ "Tenis", "Antrenament", "Divertisment", 3.2 };
	assert(cmpDescriere(a1, a2) == false);
	assert(cmpDescriere(a2, a1) == true);
}


bool cmpTipDurata(const Activitate& a1, const Activitate& a2) noexcept {
	if (a1.getTip() == a2.getTip())
	{
		return a1.getDurata() < a2.getDurata();
	}
	return a1.getTip() < a2.getTip();
}

void testCmpTipDurata() {
	Activitate a1{ "Film", "Hobby", "Divertisment", 3.2 };
	Activitate a2{ "Tenis", "Antrenament", "Divertisment", 3.7 };
	Activitate a3{ "Fotbal", "Antrenament", "Ceva", 2.4 };
	assert(cmpTipDurata(a1, a2) == true);
	assert(cmpTipDurata(a1, a3) == false);
	assert(cmpTipDurata(a2, a3) == false);
}

void testeCmpF() {
	testCmpTitlu();
	testCmpDescriere();
	testCmpTipDurata();
}
void TesteDomain() {
	testGetSet();
	testeCmpF();
}


