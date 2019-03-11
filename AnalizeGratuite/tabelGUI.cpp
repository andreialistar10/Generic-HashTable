#include "tabelGUI.h"

void TabelGUI::initComp()
{
	QVBoxLayout* layoutTabel = new QVBoxLayout;
	setLayout(layoutTabel);
	tabelPersoane->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tabelPersoane->setAlternatingRowColors(true);
	layoutTabel->addWidget(tabelPersoane);
}

void TabelGUI::reincarcaTabel()
{
	auto vect = service.getAllPersoaneService();

	tabelPersoane->setHorizontalHeaderItem(0, new QTableWidgetItem("CNP"));
	tabelPersoane->setHorizontalHeaderItem(1, new QTableWidgetItem("Nume complet"));
	tabelPersoane->setHorizontalHeaderItem(2, new QTableWidgetItem("Localitate"));
	tabelPersoane->setHorizontalHeaderItem(3, new QTableWidgetItem("Nr. telefon"));
	if (tabelPersoane->rowCount() == 0 && vect.dimensiune() != 0)
		tabelPersoane->setRowCount(1);
	
	else if (tabelPersoane->rowCount() < vect.dimensiune()) {
		tabelPersoane->insertRow(vect.dimensiune() - tabelPersoane->rowCount());
	}
	int poz{ 0 };
	for (const auto& persoana : vect) {
		tabelPersoane->setItem(poz, 0, new QTableWidgetItem(QString::number(persoana.getCNP())));
		tabelPersoane->setItem(poz, 1, new QTableWidgetItem(QString::fromStdString(persoana.getNumeComplet())));
		tabelPersoane->setItem(poz, 2, new QTableWidgetItem(QString::fromStdString(persoana.getLocalitate())));
		tabelPersoane->setItem(poz, 3, new QTableWidgetItem(QString::fromStdString(persoana.getNrTelefon())));
		poz++;
	}
	while (tabelPersoane->rowCount() > poz) {
		tabelPersoane->removeRow(poz);
	}
}
