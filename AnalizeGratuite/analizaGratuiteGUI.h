#include "tabelGUI.h"

#include<qlistwidget.h>
#include<qlineedit.h>
#include<qlayout.h>
#include<qformlayout.h>
#include<qvariant.h>
#include<qstring.h>
#include<qpushbutton.h>
#include<qmessagebox.h>
#include<qcombobox.h>
#include<qtablewidget.h>
#include <qlabel.h>

Q_DECLARE_METATYPE(Persoana);

class AnalizeGratuiteGUI: public QWidget {
private:
	QListWidget * listaPersoane;


	QPushButton* btnSterge;
	QPushButton* btnAdd;
	QPushButton* btnToatePersoanele;
	QPushButton* btnNrPersoane;
	QPushButton* btnCautaPers;

	QLineEdit* linieCNP;
	QLineEdit* linieNumeComplet;
	QLineEdit* linieLocalitate;
	QLineEdit* linieNrTelefon;

	QComboBox* comboCNP;

	TabelGUI* tabelToatePersoanele;

	Service & service;
	void initComponente();
	void conectareSemnale();
	void incarcaLista();
	
public:
	AnalizeGratuiteGUI(Service& serv) : service{ serv } {
		initComponente();
		conectareSemnale();
		incarcaLista();
	}
};