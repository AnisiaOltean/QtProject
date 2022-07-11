#pragma once

#include <QAbstractTableModel>
#include "activitate.h"
#include <vector>

using std::vector;

class MyTableModel :public QAbstractTableModel {
private:
	vector<Activitate> allAct;
public:
	MyTableModel(const vector<Activitate>& a) :allAct{ a } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return allAct.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role ) const override {
		if (role == Qt::DisplayRole) {
			Activitate a = allAct[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(a.getTitlu());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(a.getDescriere());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(a.getTip());
			}
			else if (index.column() == 3) {
				return QString::number(a.getDurata());
			}
		}
		if (role == Qt::BackgroundRole) {
			Activitate a = allAct[index.row()];
			if (a.getDurata() > 5) {
				QBrush bg{ Qt::green };
				return bg;
			}
		}
	
		return QVariant{};
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role)  const {
		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				if (section == 0) {
					return QString("Titlu");

				}
				else
					if (section == 1) {
						return QString("Descriere");
					}
					else if (section == 2) {
						return QString("Tip");
					}
					else return QString("Durata");
				//return QString("col %1").arg(section);
			}
			else
			{
				return QString("%1").arg(section);
			}
		}
		return QVariant{};
	}

	void setActs(const vector<Activitate>& acts) {
		this->allAct = acts;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
		emit layoutChanged();
	}
};