#include <QtWidgets/QApplication>
#include<iostream>
#include<sstream>
#include "qdebug.h"

#include "analizaGratuiteGUI.h"

int main(int argc, char *argv[])
{
	{
		Multime<int> m;
		m.adaugaElement(6);
		m.adaugaElement(7);
		for (const auto& el : m)
			qDebug() << el;
		QApplication a(argc, argv);
		//Repository repo;
		RepoFromFile repo("fisier.txt");
		Validator validator;
		Service serv(repo, validator);
		AnalizeGratuiteGUI analize(serv);
		analize.show();
		return a.exec();
	}
}