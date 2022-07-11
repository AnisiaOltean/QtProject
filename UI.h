#pragma once

#include "Service.h"

class ConsoleUI {
private:
	ActivitateService& srv;
public:
	//constructor UI
	ConsoleUI(ActivitateService& srv) : srv{ srv } {}
	ConsoleUI(const ActivitateService& ot) = delete;
	void printMenu();
	void uiAdd();
	void uiDelete();
	void uiModifica();
	void uiCauta();
	void uiFilterDesc();
	void uiFilterTip();
	void uiSortTitlu();
	void uiSortDesc();
	void uiSortTipDurata();
	void uiGetTip();
	void printAll();
	void printList(const vector <Activitate>& lista);
	void run();
	void UIundo();

	void printListaMenu();
	void ConsoleListaUI();
	void UIAddLista();
	void UIGoleste();
	void UIGenerare();
	void uiExport();

};



