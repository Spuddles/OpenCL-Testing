#include "convertertester.h"
#include <QFileDialog>
#include <QPainter>

#include "../Effects/GreyScale.h"
#include "../Effects/LumGreyScale.h"
#include "../Effects/ConsoleColours.h"
#include "../Effects/Fade.h"

#include "../Converters/Nearest.h"

ConverterTester::ConverterTester(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	populateEffects();
	populateConverters();

	// Hook up the timer object
	m_Timer = new QTimer(this);
	connect(m_Timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
}

ConverterTester::~ConverterTester()
{
}

void ConverterTester::populateEffects()
{
	// Create an instance of each effect and add it to the collection
	// and populate the combo box

	// Basic grayscale
	Effect *effect = new GreyScale();
	QString name = effect->getName().c_str();
	ui.effectComboBox->addItem(name);
	m_mapEffects[name] = effect;

	// Luminence based greyscale
	effect = new LumGreyScale();
	name = effect->getName().c_str();
	ui.effectComboBox->addItem(name);
	m_mapEffects[name] = effect;

	// Convert to console colours
	effect = new ConsoleColours();
	name = effect->getName().c_str();
	ui.effectComboBox->addItem(name);
	m_mapEffects[name] = effect;

	// Convert to console colours
	effect = new Fade(-30);
	name = effect->getName().c_str();
	ui.effectComboBox->addItem(name);
	m_mapEffects[name] = effect;
}

void ConverterTester::populateConverters()
{
	// Create an instance of every converter and add them
	// to the combo box and collection

	// Closest letter with black background
	Converter *converter = new Nearest();
	QString name = converter->getName().c_str();
	ui.converterComboBox->addItem(name);
	m_mapConverters[name] = converter;
}

void ConverterTester::loadImage()
{
	// Bring up the open file dialog
	QString filename = QFileDialog::getOpenFileName(this, tr("Load image file"), "", tr("Image Files (*.jpg)"));

	if (!filename.isEmpty())
	{
		QPixmap newpic(filename);
		ui.beforeImage->setPixmap(newpic);
	}
}

void ConverterTester::applyEffect()
{
	// Find out which effect I am using
	QString name = ui.effectComboBox->currentText();
	Effect *effect = m_mapEffects[name];

	// Grab the picture data from the before pixmap
	const QPixmap *before = ui.beforeImage->pixmap();

	// Make sure it's in the correct format
	QImage inputImage = before->toImage();
	if (inputImage.format() != QImage::Format_RGBA8888)
	{
		inputImage = inputImage.convertToFormat(QImage::Format_RGBA8888);
	}
	uchar* input = inputImage.bits();

	QImage outputImage = before->toImage().convertToFormat(QImage::Format_RGBA8888);
	uchar* output = outputImage.bits();

	effect->run((RGBA*)input, (RGBA*)output);

	// Apply effect
	ui.afterImage->setPixmap(QPixmap::fromImage(outputImage));
}

void ConverterTester::applyConverter()
{
}

void ConverterTester::toggleAnimation()
{
	// Start the timer control
	if (m_Timer->isActive())
	{
		m_Timer->stop();
		ui.startAnimation->setText("Start Animation");
	}
	else
	{
		m_Timer->start(10);
		ui.startAnimation->setText("Stop Animation");
	}
}

void ConverterTester::updateAnimation()
{
	static int count = 0;

	// Grab the picture data from the before pixmap
	const QPixmap *before = ui.beforeImage->pixmap();

	// Make sure it's in the correct format
	QImage inputImage = before->toImage();
	if (inputImage.format() != QImage::Format_RGBA8888)
	{
		inputImage = inputImage.convertToFormat(QImage::Format_RGBA8888);
	}
/*	uchar* input = inputImage.bits();

	// Fade everything darker
	RGBA *pixels = (RGBA*) input;
	for (int i = 0; i < 640 * 400; i++)
	{
		pixels->R = max(0, pixels->R-1);
		pixels->G = max(0, pixels->G-1);
		pixels->B = max(0, pixels->B-1);
		pixels++;
	}*/

	QPainter painter(&inputImage);
	painter.setBrush(Qt::SolidPattern);
	painter.setPen(Qt::white);
	painter.fillRect(100+count, 100+count, 100, 100, Qt::white);
	painter.end();

	// Apply effect
	ui.beforeImage->setPixmap(QPixmap::fromImage(inputImage));

	count++;
}
