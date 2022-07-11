#include "GUI.h"
#include <QString>


void GUI::initGUICmps() {
	setLayout(lymain);

	//adaugam lista
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	lst = new QListWidget;
	//new QListWidgetItem("Item 1", lst);
	//new QListWidgetItem("Item 2", lst);
	//QListWidgetItem* item3 = new QListWidgetItem("Item 3");
	//lst->insertItem(0, item3);
	vl->addWidget(lst);

	QWidget* btnDr = new QWidget;
	QGridLayout* btnCont = new QGridLayout;
	btnDr->setLayout(btnCont);
	//btnsortTitlu = new QPushButton("Sortare dupa titlu");
	//btnsortDescr = new QPushButton("Sortare dupa descriere");
	//btnsortTipDurata = new QPushButton("Sortare tip si durata");
	btnFTip = new QPushButton("Filtrare dupa tip");
	btnFDesc = new QPushButton("Filtrare descriere");
	//btnCont->addWidget(btnsortTitlu, 0,0);
	//btnCont->addWidget(btnsortDescr, 0, 1);
	//btnCont->addWidget(btnsortTipDurata, 1,0);
	btnCont->addWidget(btnFTip, 0, 0);
	btnCont->addWidget(btnFDesc, 0, 1);

	vl->addWidget(btnDr);

	//QWidget* radio = new QWidget;
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
	vl->addWidget(groupBox);

	lymain->addWidget(widDreapta);

	/*
	QWidget* wr = new QWidget;
	QVBoxLayout* wrap = new QVBoxLayout;
	wr->setLayout(wrap);*/


	//adaugam un form (vom citi detalii despre activitate)
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	titlu = new QLineEdit;
	formLDetalii->addRow(new QLabel("Titlu:"), titlu);
	descriere= new QLineEdit;
	formLDetalii->addRow(new QLabel("Descriere:"), descriere);
	tip= new QLineEdit;
	formLDetalii->addRow(new QLabel("Tip:"), tip);
	durata = new QLineEdit;
	formLDetalii->addRow(new QLabel("Durata:"), durata);

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
	formLDetalii->addWidget(winBtnst);


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
	formLDetalii->addWidget(winB2);
	
	QWidget* wcos = new QWidget;
	QHBoxLayout* lyc = new QHBoxLayout;
	wcos->setLayout(lyc);
	addCos = new QPushButton("Adauga in cos");
	stergeCos = new QPushButton("Sterge din cos");
	genereazaCos = new QPushButton("Genereaza 4 in cos");
	lyc->addWidget(addCos);
	lyc->addWidget(stergeCos);
	lyc->addWidget(genereazaCos);
	formLDetalii->addWidget(wcos);


	/*
	wrap->addWidget(widDetalii);
	*/

	lymain->addWidget(widDetalii);
	
    /*
	QWidget* w = new QWidget;
	QHBoxLayout* l = new QHBoxLayout;
	w->setLayout(l);
	QPushButton* b1 = new QPushButton("1");
	QPushButton* b2 = new QPushButton("2");
	l->addWidget(b1);
	l->addWidget(b2);

	wrap->addWidget(w);

	lymain->addWidget(wr);*/

	//lymain->addWidget(w);

}

void GUI::reloadList(const std::vector<Activitate>& activities) {
	lst->clear();
	for (const auto& a : activities) {
		//std::string info = a.getTitlu() + " | " + a.getDescriere() + " | " + a.getTip() + " | " + std::to_string(a.getDurata());
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a.getTitlu()));
		item->setData(Qt::UserRole, QString::fromStdString(a.getDescriere()));
		lst->addItem(item);
	}
}

void GUI::connectSignalsSlots() {
	//conectam semnalul de la butonul de adaugare
	QObject::connect(btnAdd, &QPushButton::clicked, this, &GUI::addAct);
	QObject::connect(btnSterge, &QPushButton::clicked, this, &GUI::stergeAct);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &GUI::modificaAct);
	//QObject::connect(btnsortTitlu, &QPushButton::clicked, this, &GUI::sortareTitlu);
	QObject::connect(btnall, &QPushButton::clicked, [=]() {
		reloadList(srv.getAllsrv());
		});
	//QObject::connect(btnsortDescr, &QPushButton::clicked, this, &GUI::sortareDescr);
	//QObject::connect(btnsortTipDurata, &QPushButton::clicked, this, &GUI::sortareTipDurata);
	QObject::connect(sort, &QPushButton::clicked, [&]() {
		if (btnsortTitlu->isChecked())
			sortareTitlu();
		else if (btnsortDescr->isChecked())
			sortareDescr();
		else if (btnsortTipDurata->isChecked())
			sortareTipDurata();
		});

	QObject::connect(btnUndo, &QPushButton::clicked, [=]() {
		try {
			srv.undo();
			reloadList(srv.getAllsrv());
		}
		catch (RepoException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.getErrmsg()));
		}
		});
	QObject::connect(btncauta, &QPushButton::clicked, this, &GUI::cauta);
	QObject::connect(btnFTip, &QPushButton::clicked, this, &GUI::filtTip);
	QObject::connect(btnFDesc, &QPushButton::clicked, this, &GUI::filtDesc);


	//useless if you ask me
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty()) {
			titlu->setText("");
			descriere->setText("");
			tip->setText("");
			durata->setText("");
		}
		else {
			auto selItem = sel.at(0);
			auto t = selItem->text();
			auto t1 = selItem->data(Qt::UserRole).toString();
			//auto t1=t.
			titlu->setText(t);
			descriere->setText(t1);
			auto r = srv.found(t.toStdString(), t1.toStdString());
			tip->setText(QString::fromStdString(r.getTip()));
			durata->setText(QString::number(r.getDurata()));
		}
		});

	QObject::connect(menuLista, &QPushButton::clicked, [&]() {
		ListaGUI* g= new ListaGUI{ srv };  //trebuie alocat dinamic deoarece daca g ar fi variabila automata (locala), fereastra ar "muri" dupa cateva milisecunde!!
	    g->show();
		});
	QObject::connect(CosCRUD, &QPushButton::clicked, [&]() {
		CosCRUDGUI* g1 = new CosCRUDGUI{ srv };
		g1->show();
		});
	QObject::connect(genereazaCos, &QPushButton::clicked, [&]() {
		int f=srv.addRandom(4);
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
	QObject::connect(CosRead, &QPushButton::clicked, [&]() {
		CosReadOnly* g2 = new CosReadOnly{srv};
		g2->show();
		});
}


void GUI::addAct() {
	try {
		srv.addActivitate(titlu->text().toStdString(), descriere->text().toStdString(), tip->text().toStdString(), durata->text().toDouble());
		reloadList(srv.getAllsrv());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrmsg()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrMsg()));
	}
}

void GUI::stergeAct() {
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
		reloadList(srv.getAllsrv());
		});
}

void GUI::filtTip() {
	auto wnd = new QWidget;
	auto tmp = new QHBoxLayout;
	auto txt = new QLineEdit;
	auto dobtn = new QPushButton("Filtreaza dupa tip!");
	tmp->addWidget(txt);
	tmp->addWidget(dobtn);
	wnd->setLayout(tmp);
	wnd->show();
	QObject::connect(dobtn, &QPushButton::clicked, [=]() {
		auto filtered=srv.filtrareTip(txt->text().toStdString());
		reloadList(filtered);
		});
}

void GUI::filtDesc() {
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


void GUI::modificaAct() {
	try {
		srv.ModificaSrv(titlu->text().toStdString(), descriere->text().toStdString(), tip->text().toStdString(), durata->text().toDouble());
		reloadList(srv.getAllsrv());
	}
	catch (RepoException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrmsg()));
	}
}

void GUI::cauta() {
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

void GUI::sortareTitlu() {
	reloadList(srv.sorteazaTitlu());
}

void GUI::sortareDescr() {
	reloadList(srv.sorteazaDescriere());
}

void GUI::sortareTipDurata() {
	reloadList(srv.sorteazaTipDurata());
}


