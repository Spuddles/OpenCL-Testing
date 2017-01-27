#ifndef CONVERTERTESTER_H
#define CONVERTERTESTER_H

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_convertertester.h"

#include "../Effects/Effect.h"
#include "../Converters/Converter.h"

class ConverterTester : public QMainWindow
{
	Q_OBJECT

public:
	ConverterTester(QWidget *parent = 0);
	~ConverterTester();

	public Q_SLOTS:
	void	loadImage();
	void	applyEffect();
	void	applyConverter();
	void	toggleAnimation();
	void	updateAnimation();

private:
	void	populateEffects();
	void	populateConverters();

	std::map<QString, Effect*>	m_mapEffects;
	std::map<QString, Converter*>	m_mapConverters;

	Ui::ConverterTesterClass ui;

	QTimer	*m_Timer;
};

#endif // CONVERTERTESTER_H
