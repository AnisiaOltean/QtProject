#pragma once
#include "Service.h"
#include <QWidget>
#include <QPainter>
#include <QRandomGenerator>
#include <QImage>
#include <QRectF>

class CosReadOnly : public QWidget, public Observer {
private:
	ActivitateService& srv;
public:
	CosReadOnly(ActivitateService& s) :srv{ s } {
		srv.addObserver(this);
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int c = 0;
		for (int i = 0; i < srv.getListaCurenta().size(); i++) {
			int x = QRandomGenerator::global()->bounded(double(this->width())-500);
			int y = QRandomGenerator::global()->bounded(double(this->height())-500);
			//QPointF center(x, y);
			qreal rx =100;
			qreal ry =100;
			//p.drawEllipse(center, rx, ry);
			QRectF target(x+c*0.5, y+c*0.5, rx, ry);
			//QRectF source(0.0, 0.0, 70.0, 40.0);
			QImage image("lamateeth.jpg");
		
			//QPainter painter(this);
			//painter.drawImage(target, image, source);
			p.drawImage(target, image);
			c += 100;
		}
	}
};