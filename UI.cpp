#include "UI.h"
#include <iostream>
using namespace std;

void ConsoleUI::printMenu() {
	cout << "1. Afisare activitati" << endl;
	cout << "2. Adauga activitate" << endl;
	cout << "3. Stergere activitati dupa titlul dat" << endl;
	cout << "4. Modificare tip si durata pt. activitatea citita" << endl;
	cout << "5. Cautare activitate (dupa titlu si descriere)" << endl;
	cout << "6. Filtrare activitati (dupa descriere)" << endl;
	cout << "7. Filtrare activitati (dupa tip)" << endl;
	cout << "8. Sortare activitati dupa titlu" << endl;
	cout << "9. Sortare activitati dupa descriere" << endl;
	cout << "10. Sortare dupa tip si durata" << endl;
	cout << "11. Meniu lista activitati" << endl;
	cout << "12. Raport dupa tip" << endl;
	cout << "13. Undo" << endl;
	cout << "0. Iesire din aplicatie" << endl;
}

void ConsoleUI::printListaMenu() {
	cout << "1. Adauga activitate dupa titlul si descrierea data" << endl;
	cout << "2. Golire lista de activitati" << endl;
	cout << "3. Generare activitati aleator" << endl;
	cout << "4. Afisare lista activitati" << endl;
	cout << "5. Exporta lista in fisier HTML" << endl;
	cout << "6. Revenire meniu principal" << endl;
}

void ConsoleUI::UIAddLista() {
	string titlu, descriere;
	cout << "Titlu: ";
	getline(cin >> ws, titlu);
	cout << "Descriere: ";
	getline(cin >> ws, descriere);
	try {
		srv.adaugaLista(titlu, descriere);
		cout << "Activitate adaugata cu succes!" << endl;
	}
	catch (RepoException& v) {
		cout << v.getErrmsg() << endl;
	}
	catch (ValidationException& e) {
		cout << e.getErrMsg() << endl;
	}
	catch (ListaException& e) {
		cout << e.getErrmsg() << endl;
	}
}
void ConsoleUI::UIGoleste() {
	srv.clearLista();
	cout << "Lista golita cu succes!" << endl;
}

void ConsoleUI::UIGenerare() {
	int cate;
	cout << "Introduceti nr. de activitati de generat: "; cin >> cate;
	cout << "S-au adaugat " << srv.addRandom(cate) << " activitati noi!" << endl;
}

void ConsoleUI::uiExport() {
	string fname;
	cout << "Dati numele fisierului: ";
	getline(cin >> ws, fname);
	try {
		srv.exportFile(fname);
		cout << "Export realizat cu succes! \n";
	}
	catch (ListaException& ve) {
		cout << ve.getErrmsg();
	}
}

void ConsoleUI::ConsoleListaUI() {
	int running = 1;
	int cmd;
	while (running) {
		printListaMenu();
		cout << "Introduceti comanda: "; cin >> cmd;
		switch (cmd) {
		case 1:
			UIAddLista();
			cout << "Exista " << srv.getListaCurenta().size() << " elemente!\n";
			break;
		case 2:
			UIGoleste();
			cout << "Exista " << srv.getListaCurenta().size() << " elemente!\n";
			break;
		case 3:
			UIGenerare();
			cout << "Exista " << srv.getListaCurenta().size() << " elemente!\n";
			break;
		case 4:
			printList(srv.getListaCurenta());
			break;
		case 5:
			uiExport();
			cout << "Exista " << srv.getListaCurenta().size() << " elemente!\n";
			break;
		case 6:
			UIGoleste();
			cout << "Bye!" << endl;
			running = 0;
			break;
		default:
			cout << "Comanda invalida!" << endl;
			break;
		}
	}
}



void ConsoleUI::uiAdd() {
	string titlu, descriere, tip;
	double durata;
	cout << "Dati titlul: ";
	getline(cin >> ws, titlu);
	cout << "Dati descrierea: ";
	getline(cin >> ws, descriere);
	cout << "Dati tipul: ";
	getline(cin >> ws, tip);
	cout << "Dati durata: ";
	cin >> durata;
	try {
		srv.addActivitate(titlu, descriere, tip, durata);
	}
	catch (RepoException& re) {
		cout << re.getErrmsg();
	}
	catch (ValidationException& ve) {
		cout << ve.getErrMsg();
	}
}

void ConsoleUI::uiDelete() {
	string titlu;
	cout << "Intorduceti titlul: ";
	getline(cin >> ws, titlu);
	srv.deleteByTitle(titlu);
}


void ConsoleUI::uiModifica() {
	string titlu, descriere, tip;
	double durata;
	cout << "Dati titlul: ";
	getline(cin >> ws, titlu);
	cout << "Dati descrierea: ";
	getline(cin >> ws, descriere);
	cout << "Dati noul tip: ";
	getline(cin >> ws, tip);
	cout << "Dati noua durata: ";
	cin >> durata;
	try {
		srv.ModificaSrv(titlu, descriere, tip, durata);
	}
	catch (RepoException& ve) {
		cout << ve.getErrmsg();
	}
}

void ConsoleUI::uiCauta() {
	string titlu, descriere;
	cout << "Dati titlul: ";
	getline(cin >> ws, titlu);
	cout << "Dati descrierea: ";
	getline(cin >> ws, descriere);
	try {
		auto f = srv.found(titlu, descriere);
		cout << f.getTitlu() << " | " << f.getDescriere() << " | " << f.getTip() << " | " << f.getDurata() << endl;
	}
	catch (RepoException& e) {
		cout << e.getErrmsg();
	}
}
void ConsoleUI::printList(const vector <Activitate>& lista) {
	if (lista.size() == 0)
	{
		cout << "Nu exista activitati in lista! " << endl;
	}
	for (const auto& a : lista) {
		cout << "Titlu: " << a.getTitlu() << " | Descriere: " << a.getDescriere() << " | Tip: " << a.getTip() << " | Durata: " << a.getDurata() << endl;
	}
}

void ConsoleUI::uiFilterDesc() {
	string descriere;
	cout << "Dati descrierea: ";
	getline(cin >> ws, descriere);
	auto filtered = srv.filtrareDescriere(descriere);
	printList(filtered);
}

void ConsoleUI::uiFilterTip() {
	string tip;
	cout << "Dati tipul: ";
	getline(cin >> ws, tip);
	auto filtered = srv.filtrareTip(tip);
	printList(filtered);
}

void ConsoleUI::uiSortTitlu() {
	auto filtered = srv.sorteazaTitlu();
	printList(filtered);
}

void ConsoleUI::uiSortDesc() {
	auto filtered = srv.sorteazaDescriere();
	printList(filtered);
}

void ConsoleUI::uiSortTipDurata() {
	auto srt = srv.sorteazaTipDurata();
	printList(srt);
}

void ConsoleUI::uiGetTip() {
	string tip;
	cout << "Introduceti tipul: ";
	getline(cin >> ws, tip);
	unordered_map<string, DTO>rez = srv.getTip(tip);
	cout << "Exista " << rez[tip].getNr() << " activitati cu tipul " << tip << "\n";
}

void ConsoleUI::printAll() {
	const vector<Activitate>& allAct = srv.getAllsrv();
	if (allAct.size() == 0)
	{
		cout << "Nu exista activitati in lista! " << endl;
	}
	for (const auto& a : allAct) {
		cout << "Titlu: " << a.getTitlu() << " | Descriere: " << a.getDescriere() << " | Tip: " << a.getTip() << " | Durata: " << a.getDurata() << endl;
	}
}

void ConsoleUI::UIundo() {
	try {
		srv.undo();
		cout << "Undo efectuat cu succes! \n";
	}
	catch (RepoException& ve) {
		cout << ve.getErrmsg();
	}
}


void ConsoleUI::run() {
	int running = 1;
	int cmd;
	while (running) {
		printMenu();
		cout << "Introduceti comanda: ";
		cin >> cmd;
		switch (cmd) {
		case 0:
			cout << "Bye!";
			running = 0;
			break;
		case 1:
			printAll();
			break;
		case 2:
			uiAdd();
			break;
		case 3:
			uiDelete();
			break;
		case 4:
			uiModifica();
			break;
		case 5:
			uiCauta();
			break;
		case 6:
			uiFilterDesc();
			break;
		case 7:
			uiFilterTip();
			break;
		case 8:
			uiSortTitlu();
			break;
		case 9:
			uiSortDesc();
			break;
		case 10:
			uiSortTipDurata();
			break;
		case 11:
			ConsoleListaUI();
			break;
		case 12:
			uiGetTip();
			break;
		case 13:
			UIundo();
			break;
		default:
			cout << "Comanda invalida!\n";
			break;
		}
	}
}


