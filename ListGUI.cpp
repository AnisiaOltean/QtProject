#include "ListGUI.h"
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>

void ListaGUI::initCmps() {
	setLayout(lymain);

	QWidget* left = new QWidget;
	QVBoxLayout* tbly = new QVBoxLayout;
	left->setLayout(tbly);
	table->setRowCount(0);
	table->setColumnCount(4);

	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Titlu" << "Descriere" << "Tip" << "Durata";
	table->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	tbly->addWidget(table);


	QWidget* right = new QWidget;
	QVBoxLayout* lyright = new QVBoxLayout;
	right->setLayout(lyright);


	QWidget* form = new QWidget;
	QFormLayout* lyform = new QFormLayout;
	form->setLayout(lyform);
	titlu = new QLineEdit;
	lyform->addRow(new QLabel("Titlu:"), titlu);
	descriere = new QLineEdit;
	lyform->addRow(new QLabel("Descriere"), descriere);
	
	lyright->addWidget(form);

	QWidget* btns = new QWidget;
	QGridLayout* lybtns = new QGridLayout;
	btns->setLayout(lybtns);
	adauga = new QPushButton("Adauga");
	generate = new QPushButton("Genereaza");
	exporta = new QPushButton("Exporta");
	clear = new QPushButton("Goleste");
	//back = new QPushButton("Iesire");

	lybtns->addWidget(adauga, 0, 0);
	lybtns->addWidget(generate, 0, 1);
	lybtns->addWidget(exporta, 1, 0);
	lybtns->addWidget(clear, 1, 1);
	//lybtns->addWidget(back, 2, 0);

	lyright->addWidget(btns);

	//QWidget* combo = new QWidget;
	combobox = new QComboBox;
	combobox->addItem("Iesire");
	combobox->addItem("Afiseaza");
	lyright->addWidget(combobox);

	lymain->addWidget(left);
	lymain->addWidget(right);
}

void ListaGUI::connectSignals() {
	QObject::connect(adauga, &QPushButton::clicked, this, &ListaGUI::add);
	QObject::connect(generate, &QPushButton::clicked, this, &ListaGUI::genereaza);
	QObject::connect(clear, &QPushButton::clicked, [&]() {
		srv.clearLista();
		QMessageBox::information(this, "Info", QString::fromStdString("Exista " + std::to_string(srv.getListaCurenta().size()) + " activitati"));
		reloadLista(srv.getListaCurenta());
		});
	QObject::connect(exporta, &QPushButton::clicked, this, &ListaGUI::toHtml);
	QObject::connect(combobox, &QComboBox::currentIndexChanged, [&]() {
		if (combobox->currentIndex() == 0) {
			QMessageBox::information(this, "Info", QString::fromStdString("Exista " + std::to_string(srv.getListaCurenta().size()) + " activitati"));
			close();
			}
		else if (combobox->currentIndex() == 1) {
			reloadLista(srv.getListaCurenta());
			QMessageBox::information(this, "Info", QString::fromStdString("Exista " + std::to_string(srv.getListaCurenta().size()) + " activitati"));
		}
		});

	//imi apar in text cand selectez elemente din tabel
	QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
		auto sel = table->selectedItems();
		int r = sel.at(0)->row();
		if (sel.isEmpty()) {
			titlu->setText("");
			descriere->setText("");
		}
		else {
			auto i1 = table->item(r, 0)->text();
			auto i2 = table->item(r, 1)->text();
			titlu->setText(i1);
			descriere->setText(i2);
		}
		});
}

void ListaGUI::add() {
	try {
		std::string t = titlu->text().toStdString();
		std::string d = descriere->text().toStdString();
		srv.adaugaLista(t, d);
		reloadLista(srv.getListaCurenta());
	}
	catch (RepoException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrmsg()));
	}
	catch (ListaException& v) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(v.getErrmsg()));
	}
	QMessageBox::information(this, "Info", QString::fromStdString("Exista "+ std::to_string(srv.getListaCurenta().size())+ " activitati"));
}

void ListaGUI::toHtml() {
	QWidget* w = new QWidget;
	QHBoxLayout* wi = new QHBoxLayout;
	w->setLayout(wi);
	QLineEdit* filename = new QLineEdit;
	QPushButton* dobtn = new QPushButton("Exporta!");
	wi->addWidget(filename);
	wi->addWidget(dobtn);
	w->show();
	QObject::connect(dobtn, &QPushButton::clicked, [=]() { //!!! nu merge cu ampersand!!!
		try {
			srv.exportFile(filename->text().toStdString());
		}
		catch (ListaException& ve) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrmsg()));
		}
		delete w;
		QMessageBox::information(this, "Info", QString::fromStdString("Exista " + std::to_string(srv.getListaCurenta().size()) + " activitati"));
		});
}


void ListaGUI::genereaza() {
	QWidget* w = new QWidget;
	QHBoxLayout* wi = new QHBoxLayout;
	w->setLayout(wi);
	QLineEdit* nr = new QLineEdit;
	QPushButton* dobtn = new QPushButton("Genereaza!");
	wi->addWidget(nr);
	wi->addWidget(dobtn);
	w->show();
	QObject::connect(dobtn, &QPushButton::clicked, [=]() { //!!! nu merge cu ampersand!!!
		//qDebug() << nr->text();
		int d = srv.addRandom(
			nr->text()
			.toInt());
		QMessageBox::information(this, "Info", QString::fromStdString("S-au adaugat "+std::to_string(d)+" activitati!"));
		reloadLista(srv.getListaCurenta());
		delete w;
		QMessageBox::information(this, "Info", QString::fromStdString("Exista " + std::to_string(srv.getListaCurenta().size()) + " activitati"));
	});
}


void ListaGUI::reloadLista(const std::vector<Activitate> all) {
	table->clearContents();
	table->setRowCount(all.size());
	int row = 0;
	for (const Activitate& a : all) {
		table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(a.getTitlu())));
		table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.getDescriere())));
		table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getTip())));
		table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(a.getDurata()))));
		row++;
	}
}


