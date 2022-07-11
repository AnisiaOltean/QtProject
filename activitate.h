#pragma once

#include <string>
#include <iostream>
using std::string;

class Activitate {
private:
	string titlu;
	string descriere;
	string tip;
	double durata;
public:
	Activitate() = delete;

	//constructor cu parametri
	Activitate(string titlu, string descriere, string tip, double durata) :titlu{ titlu }, descriere{ descriere }, tip{ tip }, durata{ durata } {}

	//copy constructor
	Activitate(const Activitate& ot) : titlu{ ot.titlu }, descriere{ ot.descriere }, tip{ ot.tip }, durata{ ot.durata }{
		std::cout << "!!!!\n";
	}

	string getTitlu() const noexcept;
	string getDescriere() const noexcept;
	string getTip() const noexcept;
	double getDurata() const noexcept;

	void setTitlu(string TitluNou);
	void setDescriere(string DescrNoua);
	void setTip(string TipNou);
	void setDurata(double DurataNoua) noexcept;

};

bool cmpTitlu(const Activitate& a1, const Activitate& a2) noexcept;
/*
* Compara titlul a 2 activitati
* @return: True daca a1.true()<=a2.titlu(), false altfel
*/

bool cmpDescriere(const Activitate& a1, const Activitate& a2) noexcept;
/*
* Compara descrierea a 2 activitati
* @return: True daca a1.descriere()<=a2.descriere(), false altfel
*/

bool cmpTipDurata(const Activitate& a1, const Activitate& a2) noexcept;
/*
* Compara 2 activitati dupa tip si durata
* @return: True daca a1.tip()<a2.tip(), sau a1.tip()<a2.tip() si a1.getDurata()<a2.getDurata(),
  false altfel
*/

void TesteDomain();




