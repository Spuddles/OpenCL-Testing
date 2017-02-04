#ifndef CONVERTERTESTER_H
#define CONVERTERTESTER_H

#include <chrono>
#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_convertertester.h"

#include "../Effects/Effect.h"
#include "../Converters/Converter.h"
#include "../Generators/Generator.h"

class ConverterTester : public QMainWindow
{
	Q_OBJECT

public:
	ConverterTester(QWidget *parent = 0);
	~ConverterTester();

	public Q_SLOTS:
	void	loadImage();
	void	applyEffect(RGBA *image, QImage &outputImage);
	void	applyConverter(RGBA *image);
	void	toggleAnimation();
	void	updateAnimation();

private:
	void	populateGenerators();
	void	populateEffects();
	void	populateConverters();

	std::map<QString, Generator*>	m_mapGenerators;
	std::map<QString, Effect*>		m_mapEffects;
	std::map<QString, Converter*>	m_mapConverters;

	Ui::ConverterTesterClass ui;

	QTimer	*m_Timer;
	std::chrono::system_clock::time_point	m_StartTime;
};

#endif // CONVERTERTESTER_H
