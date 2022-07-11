#pragma once

#include "Service.h"
#include "ListGUI.h"
#include "CosCRUDGUI.h"
#include "CosReadOnly.h"
#include <qwidget.h>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>

class GUI : public QWidget {
private:
	ActivitateService& srv;
	QHBoxLayout* lymain = new QHBoxLayout;
	QListWidget* lst;
	QLineEdit* titlu;
	QLineEdit* descriere;
	QLineEdit* tip;
	QLineEdit* durata;
	QPushButton* btnAdd;
	QPushButton* btnSterge;
	QPushButton* btnModifica;
	QRadioButton* btnsortTitlu;
	QRadioButton* btnsortDescr;
	QRadioButton* btnsortTipDurata;
	QPushButton* btnall;
	QPushButton* btncauta;
	QPushButton* btnUndo;
	QPushButton* sort;
	QPushButton* btnFDesc;
	QPushButton* btnFTip;
	QPushButton* menuLista;
	QPushButton* CosCRUD;
	QPushButton* CosRead;
	QPushButton* addCos;
	QPushButton* stergeCos;
	QPushButton* genereazaCos;

	QRadioButton* radioSrtArtistTitlu;
	QRadioButton* radioSrtDurata;
	QPushButton* btnSortSongs;

	void initGUICmps();

	void reloadList(const std::vector<Activitate>& activities);
	void connectSignalsSlots();
	void addAct();
	void stergeAct();
	void modificaAct();

	void sortareTitlu();
	void sortareDescr();
	void sortareTipDurata();
	void cauta();
	void filtTip();
	void filtDesc();

public:
	GUI(ActivitateService& srv) :srv{ srv } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(srv.getAllsrv());
	}

};