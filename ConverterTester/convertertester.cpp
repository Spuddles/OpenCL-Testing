#include "convertertester.h"
#include <QFileDialog>

#include "../Effects/GreyScale.h"
#include "../Effects/LumGreyScale.h"
#include "../Effects/ConsoleColours.h"

ConverterTester::ConverterTester(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	populateEffects();
}

ConverterTester::~ConverterTester()
{
}

void ConverterTester::populateEffects()
{
	// Create an instance of each effect and add it to the coolection
	// and populate the combo box

	// Basic grayscale
	Effect *effect = new GreyScale();
	QString name = effect->getName().c_str();
	ui.comboBox->addItem(name);
	m_mapEffects[name] = effect;

	// Luminence based greyscale
	effect = new LumGreyScale();
	name = effect->getName().c_str();
	ui.comboBox->addItem(name);
	m_mapEffects[name] = effect;

	// Convert to console colours
	effect = new ConsoleColours();
	name = effect->getName().c_str();
	ui.comboBox->addItem(name);
	m_mapEffects[name] = effect;
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
	QString name = ui.comboBox->currentText();
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

