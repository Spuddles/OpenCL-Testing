#ifndef CONVERTERTESTER_H
#define CONVERTERTESTER_H

#include <QtWidgets/QMainWindow>
#include "ui_convertertester.h"

class ConverterTester : public QMainWindow
{
	Q_OBJECT

public:
	ConverterTester(QWidget *parent = 0);
	~ConverterTester();

	public Q_SLOTS:
	void	loadImage();
	void	applyEffect();

private:
	Ui::ConverterTesterClass ui;
};

#endif // CONVERTERTESTER_H
