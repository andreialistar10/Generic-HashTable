#include "analizaGratuiteGUI.h"

void AnalizeGratuiteGUI::initComponente()
{
	QHBoxLayout* layoutAplicatie = new QHBoxLayout;
	setLayout(layoutAplicatie);

	//Partea stanga
	QWidget* stanga = new QWidget;
	QVBoxLayout* layoutSt = new QVBoxLayout;
	stanga->setLayout(layoutSt);


	//Text deasupra listei
	QLabel* text = new QLabel("CNP-urile tuturor persoanelor:");
	text->setAlignment(Qt::AlignCenter);
	layoutSt->addWidget(text);
	layoutSt->addStretch();
	//Lista de persoane
	listaPersoane = new QListWidget;
	layoutSt->addWidget(listaPersoane);

	//buton sterge
	btnSterge = new QPushButton("&Stege");
	btnSterge->setEnabled(false);
	layoutSt->addStretch();
	layoutSt->addWidget(btnSterge);
	layoutSt->addStretch();

	//Partea dreapta
	QWidget* dreapta = new QWidget;
	QVBoxLayout* layoutDr = new QVBoxLayout;
	dreapta->setLayout(layoutDr);

	//linii informatii

	QWidget* widgetInformatii = new QWidget;
	QFormLayout* layoutInfo = new QFormLayout;
	widgetInformatii->setLayout(layoutInfo);

	linieCNP = new QLineEdit;
	linieNumeComplet = new QLineEdit;
	linieLocalitate = new QLineEdit;
	linieNrTelefon = new QLineEdit;

	layoutInfo->addRow("CNP:", linieCNP);
	layoutInfo->addRow("Nume complet:", linieNumeComplet);
	layoutInfo->addRow("Localitate:", linieLocalitate);
	layoutInfo->addRow("Nr Telefon:", linieNrTelefon);

	layoutDr->addWidget(widgetInformatii);

	//butoane adauga, toate persoanele, nrTotal
	QWidget* widgetBTNadd =  new QWidget;
	QHBoxLayout* layoutBTNadd = new QHBoxLayout;
	widgetBTNadd->setLayout(layoutBTNadd);

	btnAdd = new QPushButton("Adauga");
	//btnAdd->setEnabled(false);
	btnToatePersoanele = new QPushButton("Afiseaza toate persoanele");
	btnNrPersoane = new QPushButton("Nr total persoane");

	layoutBTNadd->addStretch();
	layoutBTNadd->addWidget(btnAdd);
	layoutBTNadd->addStretch();
	layoutBTNadd->addWidget(btnToatePersoanele);
	layoutBTNadd->addStretch();
	layoutBTNadd->addWidget(btnNrPersoane);
	layoutBTNadd->addStretch();

	layoutDr->addWidget(widgetBTNadd);
	//btn cauta dupa CNP
	QWidget* widgetCautaCNP = new QWidget;
	QHBoxLayout* layoutCautaCNP = new QHBoxLayout;
	widgetCautaCNP->setLayout(layoutCautaCNP);

	btnCautaPers = new QPushButton("Cauta dupa CNP-ul");
	comboCNP = new QComboBox;
	
	
	layoutCautaCNP->addStretch();
	layoutCautaCNP->addWidget(btnCautaPers);
	layoutCautaCNP->addStretch();
	layoutCautaCNP->addWidget(comboCNP);
	layoutCautaCNP->addStretch();

	layoutDr->addWidget(widgetCautaCNP);

	layoutAplicatie->addWidget(stanga);
	layoutAplicatie->addWidget(dreapta);
}

void AnalizeGratuiteGUI::conectareSemnale()
{

	//Conectam selectarea unui item din lista

	QObject::connect(listaPersoane, &QListWidget::itemSelectionChanged, [&]() {
		if (listaPersoane->selectedItems().empty()) {
			btnSterge->setEnabled(false);
			linieCNP->setText("");
			linieNumeComplet->setText("");
			linieLocalitate->setText("");
			linieNrTelefon->setText("");
			return;
		}
		btnSterge->setEnabled(true);
		QListWidgetItem* persoanaSelectata = listaPersoane->selectedItems().at(0);
		auto persoana = persoanaSelectata->data(Qt::UserRole).value<Persoana>();
		linieCNP->setText(QString::number(persoana.getCNP()));
		linieNumeComplet->setText(QString::fromStdString(persoana.getNumeComplet()));
		linieLocalitate->setText(QString::fromStdString(persoana.getLocalitate()));
		linieNrTelefon->setText(QString::fromStdString(persoana.getNrTelefon()));
		btnAdd->setEnabled(false);
	});

	//Conectam butonul de Sterere

	QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
		auto persoana = listaPersoane->selectedItems().at(0)->data(Qt::UserRole).value<Persoana>();
		try {
			service.stergeService(persoana);
			incarcaLista();
		}
		catch (Exceptii<Repository>& ex) {
			QMessageBox::warning(this, "Persoana inexistenta!", QString::fromStdString(ex.getMesajExceptie()));
		}
	});

	//Conectam butonul de ADD
	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		auto CNP = linieCNP->text().toStdString();
		auto numeComplet = linieNumeComplet->text().toStdString();
		auto localitate = linieLocalitate->text().toStdString();
		auto nrTelefon = linieNrTelefon->text().toStdString();
		try {
			auto persoana = service.creeazaPersoana(CNP, numeComplet, localitate, nrTelefon);
			service.adaugaService(persoana);
			QListWidgetItem* persoanaNoua=new QListWidgetItem (QString::fromStdString(CNP), listaPersoane);
			persoanaNoua->setData(Qt::UserRole, QVariant::fromValue<Persoana>(persoana));
			comboCNP->addItem(QString::fromStdString(CNP), QVariant::fromValue<Persoana>(persoana));
			comboCNP->setSizeAdjustPolicy(QComboBox::AdjustToContents);
			btnToatePersoanele->setEnabled(true);
			btnCautaPers->setEnabled(true);
			comboCNP->setEnabled(true);
		}
		catch (Exceptii<Validator>& ex) {
			QMessageBox::warning(this, "Date invalide!", QString::fromStdString(ex.getMesajExceptie()));
		}

		catch (Exceptii<Repository>& ex) {
			QMessageBox::warning(this,"Persoana existenta!", QString::fromStdString(ex.getMesajExceptie()));
		}
		linieCNP->setText("");
		linieNumeComplet->setText("");
		linieLocalitate->setText("");
		linieNrTelefon->setText("");
	});

	//Facem activ sau inactiv butonul de adaugare
	QObject::connect(linieCNP, &QLineEdit::textChanged, [&]() {
		if (linieCNP->text() == "" || linieNumeComplet->text() == "" || linieLocalitate->text() == "" || linieNrTelefon->text() == "") {
			btnAdd->setEnabled(false);
			return;
		}
		btnAdd->setEnabled(true);
	});
	QObject::connect(linieNumeComplet, &QLineEdit::textChanged, [&]() {
		if (linieCNP->text() == "" || linieNumeComplet->text() == "" || linieLocalitate->text() == "" || linieNrTelefon->text() == "") {
			btnAdd->setEnabled(false);
			return;
		}
		btnAdd->setEnabled(true);
	});
	QObject::connect(linieLocalitate, &QLineEdit::textChanged, [&]() {
		if (linieCNP->text() == "" || linieNumeComplet->text() == "" || linieLocalitate->text() == "" || linieNrTelefon->text() == "") {
			btnAdd->setEnabled(false);
			return;
		}
		btnAdd->setEnabled(true);
	});

	QObject::connect(linieNrTelefon, &QLineEdit::textChanged, [&]() {
		if (linieCNP->text() == "" || linieNumeComplet->text() == "" || linieLocalitate->text() == "" || linieNrTelefon->text() == "") {
			btnAdd->setEnabled(false);
			return;
		}
		btnAdd->setEnabled(true);
	});

	QObject::connect(btnNrPersoane, &QPushButton::clicked, [&]() {
		QMessageBox::information(this, "Numarul total de persoane", "Numarul total de persoane inscrise in momentul de fata este: " + QString::number(service.getAllPersoaneService().dimensiune()) + "!");
	});

	QObject::connect(btnCautaPers, &QPushButton::clicked, [&]() {
		auto CNP = comboCNP->currentText();
		auto persoana = comboCNP->currentData(Qt::UserRole).value<Persoana>();
		QString detaliiPersoana = "CNP: " + CNP + "\nNume complet: "+ QString::fromStdString(persoana.getNumeComplet())+"\nLocalitatea: "+QString::fromStdString(persoana.getLocalitate())+"\nNr. telefon: "+ QString::fromStdString(persoana.getNrTelefon()+"\n");
		QMessageBox::information(this, "Informatii despre " + QString::fromStdString(persoana.getNumeComplet()), detaliiPersoana);
	});
	QObject::connect(btnToatePersoanele, &QPushButton::clicked, [&]() {
		tabelToatePersoanele = new TabelGUI(service);
		tabelToatePersoanele->show();
	});
}

void AnalizeGratuiteGUI::incarcaLista()
{
	listaPersoane->clear();
	auto vect = service.getAllPersoaneService();
	if (vect.vida()) {
		btnToatePersoanele->setEnabled(false);
		btnCautaPers->setEnabled(false);
		comboCNP->clear();
		comboCNP->setEnabled(false);
		btnSterge->setEnabled(false);
		return;
	}
	btnToatePersoanele->setEnabled(true);
	btnCautaPers->setEnabled(true);
	comboCNP->setEnabled(true);
	for (const auto& persoana : vect) {
		QListWidgetItem* persoanaActuala = new QListWidgetItem(QString::number(persoana.getCNP()), listaPersoane);
		persoanaActuala->setData(Qt::UserRole, QVariant::fromValue<Persoana>(persoana));
	}
	comboCNP->clear();
	for (const auto&persoana : vect) {
		comboCNP->addItem(QString::number(persoana.getCNP()),QVariant::fromValue<Persoana>(persoana));
		//comboCNP->setFixedSize(QString::number(persoana.getCNP()).size());
	}
}
