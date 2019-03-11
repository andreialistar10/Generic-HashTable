#pragma once
#include "service.h"
#include <qtablewidget.h>
#include <qwidget.h>
#include <qlayout.h>

class TabelGUI: public QWidget, public Observer {

private:
	Service & service;
	QTableWidget* tabelPersoane= new QTableWidget(service.getNrTotalPersoane(), 4);;
	void initComp();
	void reincarcaTabel();
public:
	void update() override {
		//tabelPersoane->deleteLater();
		//QTableWidget* t;
		//tabelPersoane = t;
		reincarcaTabel();
	}

	TabelGUI(Service& serv) : service{ serv } {
		serv.addObserver(this);
		initComp();
		reincarcaTabel();
	}
};