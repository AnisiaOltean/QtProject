#pragma once
#include "Service.h"
#include "Observer.h"
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QListWidget>


//Fiecare cos retine referinta la acelasi service
//Deci: ActivitateService- clasa observable
//CosCRUDGUI- clasa Observer

class CosCRUDGUI : public QWidget, public Observer {
private:
	ActivitateService& srv;
	QHBoxLayout* lymain = new QHBoxLayout;
	QListWidget* lst = new QListWidget;
	QPushButton* genereaza2;
	QPushButton* golsete;

	void initCmps();
	void connectSignals();
	void reloadLista(vector<Activitate> allA);

public:
	CosCRUDGUI(ActivitateService& s) :srv{ s } {
		initCmps();
		connectSignals();
		reloadLista(srv.getListaCurenta());
	}

	void update() override {
		reloadLista(srv.getListaCurenta());
	}
	~CosCRUDGUI() {
		srv.removeObserver(this);
	}
};