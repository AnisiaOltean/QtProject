#pragma once
#include "Service.h"
#include "activitate.h"
#include <qwidget.h>
#include <qlayout.h>
#include <qtablewidget.h>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>

class ListaGUI : public QWidget {
private:
	ActivitateService& srv;
	QHBoxLayout* lymain = new QHBoxLayout;
	QTableWidget* table = new QTableWidget;
	QLineEdit* titlu;
	QLineEdit* descriere;
	QPushButton* adauga;
	QPushButton* clear; 
	QPushButton* generate; 
	QPushButton* exporta; 
	QComboBox* combobox;


	void initCmps();
	void connectSignals();
	void reloadLista(const std::vector<Activitate> all);

	void add();
	void genereaza();
	void toHtml();

public:
	ListaGUI(ActivitateService& srv): srv{srv}{
		initCmps();
		connectSignals();
		reloadLista(srv.getListaCurenta());
	}

};