#include "convertertester.h"
#include <QFileDialog>

ConverterTester::ConverterTester(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

ConverterTester::~ConverterTester()
{

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

	// Grab the picture data from the before pixmap
	const QPixmap *before = ui.beforeImage->pixmap();

	QImage image = before->toImage();

	uchar* bits = image.bits();

	for (int i = 0; i < 640 * 400 * 4; i += 4)
	{
		bits[i]   = bits[i] + 10 % 255;
		bits[i+1] = bits[i] + 10 % 255;
		bits[i+2] = bits[i] + 10 % 255;
	}

	// Apply effect
	ui.afterImage->setPixmap(QPixmap::fromImage(image));
}

