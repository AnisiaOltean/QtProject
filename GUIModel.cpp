#include "GUIModel.h"
#include <QMessageBox>
#include "ListGUI.h"
#include <QHeaderView>

void GUIModel::initCmps() {
	setLayout(lymain);

	QWidget* left = new QWidget;
	QVBoxLayout* lyleft = new QVBoxLayout;
	left->setLayout(lyleft);
	lyleft->addWidget(tbl);

	QWidget* btnDr = new QWidget;
	QGridLayout* btnCont = new QGridLayout;
	btnDr->setLayout(btnCont);
	btnFTip = new QPushButton("Filtrare dupa tip");
	btnFDesc = new QPushButton("Filtrare descriere");
	btnCont->addWidget(btnFTip, 0, 0);
	btnCont->addWidget(btnFDesc, 0, 1);
	lyleft->addWidget(btnDr);

	QHBoxLayout* lyRadioBox = new QHBoxLayout;
	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));
	groupBox->setLayout(lyRadioBox);
	btnsortTitlu = new QRadioButton("Sortare dupa titlu");
	btnsortDescr = new QRadioButton("Sortare dupa descriere");
	btnsortTipDurata = new QRadioButton("Sortare tip si durata");
	sort = new QPushButton("Sorteaza!");
	lyRadioBox->addWidget(btnsortTitlu);
	lyRadioBox->addWidget(btnsortDescr);
	lyRadioBox->addWidget(btnsortTipDurata);
	lyRadioBox->addWidget(sort);
	lyleft->addWidget(groupBox);

	QWidget* right = new QWidget;
	QVBoxLayout* lyright = new QVBoxLayout;
	right->setLayout(lyright);

	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	titlu = new QLineEdit;
	formLDetalii->addRow(new QLabel("Titlu:"), titlu);
	descriere = new QLineEdit;
	formLDetalii->addRow(new QLabel("Descriere:"), descriere);
	tip = new QLineEdit;
	formLDetalii->addRow(new QLabel("Tip:"), tip);
	durata = new QLineEdit;
	formLDetalii->addRow(new QLabel("Durata:"), durata);
	lyright->addWidget(widDetalii);

	//adaugam butoane
	QWidget* winBtnst = new QWidget;
	QHBoxLayout* btnstl = new QHBoxLayout;
	winBtnst->setLayout(btnstl);
	btnAdd = new QPushButton("Adauga");
	btnSterge = new QPushButton("Sterge");
	btnModifica = new QPushButton("Modifica");
	btnall = new QPushButton("Afiseaza");
	btnstl->addWidget(btnAdd);
	btnstl->addWidget(btnSterge);
	btnstl->addWidget(btnModifica);
	btnstl->addWidget(btnall);
	lyright->addWidget(winBtnst);

	QWidget* winB2 = new QWidget;
	QGridLayout* btn2 = new QGridLayout;
	winB2->setLayout(btn2);
	btncauta = new QPushButton("Cauta activitate");
	btnUndo = new QPushButton("Undo");
	btnUndo->setStyleSheet("background-color: rgb(127, 227, 91);");
	menuLista = new QPushButton("Meniu Lista");
	menuLista->setStyleSheet("background-color: #40dbe3;");
	btn2->addWidget(btncauta, 0, 0);
	btn2->addWidget(btnUndo, 0, 1);
	btn2->addWidget(menuLista, 1, 0, 1, 2);
	CosCRUD = new QPushButton("Deschide COS CRUD");
	CosRead = new QPushButton("Deschide COS Read-Only");
	btn2->addWidget(CosCRUD, 2, 0);
	btn2->addWidget(CosRead, 2, 1);
	lyright->addWidget(winB2);

	QWidget* wcos = new QWidget;
	QHBoxLayout* lyc = new QHBoxLayout;
	wcos->setLayout(lyc);
	addCos = new QPushButton("Adauga in cos");
	stergeCos = new QPushButton("Sterge din cos");
	genereazaCos = new QPushButton("Genereaza 4 in cos");
	lyc->addWidget(addCos);
	lyc->addWidget(stergeCos);
	lyc->addWidget(genereazaCos);
	lyright->addWidget(wcos);

	lymain->addWidget(left);
	lymain->addWidget(right);
}

void GUIModel::connectSignals() {
	QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tbl->selectionModel()->selectedIndexes().isEmpty()) {
			titlu->setText("");
			descriere->setText("");
			tip->setText("");
			durata->setText("");
			return;
		}
		int selRow = tbl->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tbl->model()->index(selRow, 0);
		auto cel0Value = tbl->model()->data(cel0Index, Qt::DisplayRole).toString();
		titlu->setText(cel0Value);
		auto cel1Index = tbl->model()->index(selRow, 1);
		auto cel1Value = tbl->model()->data(cel1Index, Qt::DisplayRole).toString();
		descriere->setText(cel1Value);
		auto cel2Index = tbl->model()->index(selRow, 2);
		auto cel2Value = tbl->model()->data(cel2Index, Qt::DisplayRole).toString();
		tip->setText(cel2Value);
		auto cel3index = tbl->model()->index(selRow, 3);
		auto cel3value = tbl->model()->data(cel3index, Qt::DisplayRole).toString();
		durata->setText(cel3value);
		});
	QObject::connect(btnAdd, &QPushButton::clicked, this, &GUIModel::addAct);
	QObject::connect(btnSterge, &QPushButton::clicked, this, &GUIModel::stergeAct);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &GUIModel::modificaAct);
	QObject::connect(btnall, &QPushButton::clicked, [&]() {
		reloadList(srv.getAllsrv());
		});
	QObject::connect(sort, &QPushButton::clicked, [&]() {
		if (btnsortTitlu->isChecked())
			sortareTitlu();
		else if (btnsortDescr->isChecked())
			sortareDescr();
		else if (btnsortTipDurata->isChecked())
			sortareTipDurata();
		});
	QObject::connect(btnFDesc, &QPushButton::clicked, this, &GUIModel::filtDesc1);
	QObject::connect(btnFTip, &QPushButton::clicked, this, &GUIModel::filtTip1);
	QObject::connect(btncauta, &QPushButton::clicked, this, &GUIModel::cauta1);
	QObject::connect(btnUndo, &QPushButton::clicked, [=]() {
		try {
			srv.undo();
			reloadList(srv.getAllsrv());
		}
		catch (RepoException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.getErrmsg()));
		}
		});
	QObject::connect(menuLista, &QPushButton::clicked, [&]() {
		ListaGUI* g = new ListaGUI{ srv };  //trebuie alocat dinamic deoarece daca g ar fi variabila automata (locala), fereastra ar "muri" dupa cateva milisecunde!!
		g->show();
		});
	QObject::connect(CosCRUD, &QPushButton::clicked, [&]() {
		CosCRUDGUI* g1 = new CosCRUDGUI{ srv };
		g1->show();
		});
	QObject::connect(CosRead, &QPushButton::clicked, [&]() {
		CosReadOnly* g2 = new CosReadOnly{ srv };
		g2->show();
		});
	QObject::connect(genereazaCos, &QPushButton::clicked, [&]() {
		int f = srv.addRandom(4);
		QMessageBox::information(this, "Info", "S-au adaugat " + QString::number(f) + " activitati");
		//nu mai trebuie reload deoarece acesta se apeleaza oricum la notify!
		});
	QObject::connect(stergeCos, &QPushButton::clicked, [&]() {
		srv.stergeTitlu(titlu->text().toStdString());
		});
	QObject::connect(addCos, &QPushButton::clicked, [&]() {
		try {
			srv.adaugaLista(titlu->text().toStdString(), descriere->text().toStdString());
		}
		catch (RepoException& ve) {
			QMessageBox::warning(this, "Exceptie", QString::fromStdString(ve.getErrmsg()));
		}
		catch (ListaException& ve) {
			QMessageBox::warning(this, "Exceptie", QString::fromStdString(ve.getErrmsg()));
		}
		});
}

void GUIModel::addAct() {
	try {
		srv.addActivitate(titlu->text().toStdString(), descriere->text().toStdString(), tip->text().toStdString(), durata->text().toDouble());
		reloadList(srv.getAllsrv());
		QMessageBox::information(this, "Info", "Activitate adaugata cu succes!");
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrmsg()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrMsg()));
	}
}

void GUIModel::stergeAct() {
	auto wnd = new QWidget;
	auto tmp = new QHBoxLayout;
	auto txt = new QLineEdit;
	auto dobtn = new QPushButton("Sterge!");
	tmp->addWidget(txt);
	tmp->addWidget(dobtn);
	wnd->setLayout(tmp);
	wnd->show();
	QObject::connect(dobtn, &QPushButton::clicked, [=]() {
		srv.deleteByTitle(txt->text().toStdString());
		QMessageBox::information(this, "Info", "Activitate stearsa cu succes!");
		reloadList(srv.getAllsrv());
		});
}

void GUIModel::modificaAct() {
	try {
		srv.ModificaSrv(titlu->text().toStdString(), descriere->text().toStdString(), tip->text().toStdString(), durata->text().toDouble());
		reloadList(srv.getAllsrv());
		QMessageBox::information(this, "Info", "Activitate modificata cu succes!");
	}
	catch (RepoException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrmsg()));
	}
}

void GUIModel::sortareTitlu() {
	reloadList(srv.sorteazaTitlu());
	QMessageBox::information(this, "Info", "Sortat");
}

void GUIModel::sortareDescr() {
	reloadList(srv.sorteazaDescriere());
	QMessageBox::information(this, "Info", "Sortat");
}

void GUIModel::sortareTipDurata() {
	reloadList(srv.sorteazaTipDurata());
	QMessageBox::information(this, "Info", "Sortat");
}

void GUIModel::filtTip1() {
	auto wnd = new QWidget;
	auto tmp = new QHBoxLayout;
	auto txt = new QLineEdit;
	auto dobtn = new QPushButton("Filtreaza dupa tip!");
	tmp->addWidget(txt);
	tmp->addWidget(dobtn);
	wnd->setLayout(tmp);
	wnd->show();
	QObject::connect(dobtn, &QPushButton::clicked, [=]() {
		auto filtered = srv.filtrareTip(txt->text().toStdString());
		reloadList(filtered);
		});
}

void GUIModel::filtDesc1() {
	auto wnd = new QWidget;
	auto tmp = new QHBoxLayout;
	auto txt = new QLineEdit;
	auto dobtn = new QPushButton("Filtreaza dupa descriere!");
	tmp->addWidget(txt);
	tmp->addWidget(dobtn);
	wnd->setLayout(tmp);
	wnd->show();
	QObject::connect(dobtn, &QPushButton::clicked, [=]() {
		auto filtered = srv.filtrareDescriere(txt->text().toStdString());
		reloadList(filtered);
		});
}

void GUIModel::cauta1() {
	auto wnd = new QWidget;
	auto tmp = new QFormLayout;
	auto title = new QLineEdit;
	auto descr = new QLineEdit;
	auto dobtn = new QPushButton("Cauta activitate!");
	wnd->setLayout(tmp);
	tmp->addRow(new QLabel("Titlu:"), title);
	tmp->addRow(new QLabel("Descriere:"), descr);
	tmp->addWidget(dobtn);
	wnd->show();
	QObject::connect(dobtn, &QPushButton::clicked, [=]() {
		try {
			Activitate a = srv.found(title->text().toStdString(), descr->text().toStdString());
			QString info = QString::fromStdString(a.getTitlu()) + " | " + QString::fromStdString(a.getDescriere());
			QMessageBox::information(this, "Activitate cautata:", info);
		}
		catch (RepoException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.getErrmsg()));
		}
		});
}

void GUIModel::reloadList(vector <Activitate> acts) {
	model->setActs(acts);
}
