#pragma once

#include <QAbstractTableModel>
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
#include <QRadioButton>
#include <QGroupBox>
#include <QFormLayout>
#include "MyTableView.h"
#include "CosCRUDGUI.h"
#include "CosReadOnly.h"

class GUIModel :public QWidget {
private:
	ActivitateService& srv;
	QHBoxLayout* lymain = new QHBoxLayout;
	MyTableModel* model;
	QTableView* tbl= new QTableView;


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

	void initCmps();
	void connectSignals();
	void reloadList(vector <Activitate> acts);
	void addAct();
	void stergeAct();
	void modificaAct();
	void sortareTitlu();
	void sortareDescr();
	void sortareTipDurata();

	void filtTip1();
	void filtDesc1();
	void cauta1();

	
public:
	GUIModel(ActivitateService& s) :srv{ s } {
		initCmps();
		model = new MyTableModel{ srv.getAllsrv() };
		tbl->setModel(model);
		connectSignals();
	}
};