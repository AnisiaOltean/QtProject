#include "CosCRUDGUI.h"
#include <QMessageBox>

void CosCRUDGUI::initCmps() {
	setLayout(lymain);

	QWidget* right = new QWidget;
	QVBoxLayout* lyright = new QVBoxLayout;
	right->setLayout(lyright);

	QWidget* left = new QWidget;
	QVBoxLayout* lyleft=  new QVBoxLayout;
	left->setLayout(lyleft);
	lyleft->addWidget(lst);

	QWidget* wbtn = new QWidget;
	QVBoxLayout* lyb = new QVBoxLayout;
	wbtn->setLayout(lyb);
	genereaza2 = new QPushButton("Genereaza 4");
	golsete = new QPushButton("Goleste cos");
	lyb->addWidget(genereaza2);
	lyb->addWidget(golsete);
	lyright->addWidget(wbtn);

	lymain->addWidget(left);
	lymain->addWidget(right);
}

void CosCRUDGUI::connectSignals() {
	srv.addObserver(this);
	QObject::connect(genereaza2, &QPushButton::clicked, [&]() {
		int add=srv.addRandom(4);
		QMessageBox::information(this, "Info", "S-au adaugat " + QString::number(add) + " activitati");
		reloadLista(srv.getListaCurenta());
		});
	QObject::connect(golsete, &QPushButton::clicked, [&]() {
		srv.clearLista();
		QMessageBox::information(this, "Info", "Lista golita");
		reloadLista(srv.getListaCurenta());
		});
}

void CosCRUDGUI::reloadLista(vector<Activitate>allA) {
	lst->clear();
	for (const auto& a : allA) {
		std::string info = a.getTitlu() + " | " + a.getDescriere() + " | " + a.getTip() + " | " + std::to_string(a.getDurata());
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(info));
		item->setData(Qt::UserRole, QString::fromStdString(a.getDescriere()));
		lst->addItem(item);
	}
}

