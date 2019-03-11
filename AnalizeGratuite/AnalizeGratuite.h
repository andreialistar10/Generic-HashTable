#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AnalizeGratuite.h"

class AnalizeGratuite : public QMainWindow
{
	Q_OBJECT

public:
	AnalizeGratuite(QWidget *parent = Q_NULLPTR);

private:
	Ui::AnalizeGratuiteClass ui;
};
