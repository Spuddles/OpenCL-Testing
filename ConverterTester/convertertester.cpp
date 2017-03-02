#include "convertertester.h"
#include <QFileDialog>
#include <QPainter>

#include "../Effects/GreyScale.h"
#include "../Effects/BlackAndWhite.h"
#include "../Effects/LumGreyScale.h"
#include "../Effects/ConsoleColours.h"
#include "../Effects/Fade.h"

#include "../Converters/Nearest.h"
#include "../Converters/FullBlock.h"
#include "../Converters/HalfBlock.h"

#include "../Generators/ColourTest.h"
#include "../Generators/StaticImage.h"
#include "../Generators/BounceImage.h"
#include "../Generators/RealtimeGraphics.h"

#include "../Utils/Timer.h"

#include <sstream>

ConverterTester::ConverterTester(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
	populateGenerators();
	populateEffects();
	populateConverters();

	// Hook up the timer object
	m_Timer = new QTimer(this);
	connect(m_Timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
}

ConverterTester::~ConverterTester()
{
}

void ConverterTester::populateGenerators()
{
	// Create an instance of every generator and add them
	// to the combo box and collection

	// Colour Sweep
	Generator *generator = new ColourTest();
	QString name;
	if (generator->initialise())
	{
		name = generator->getName().c_str();
		ui.generatorComboBox->addItem(name);
		m_mapGenerators[name] = generator;
	}

	generator = new RealtimeGraphics();
	if (generator->initialise())
	{
		name = generator->getName().c_str();
		ui.generatorComboBox->addItem(name);
		m_mapGenerators[name] = generator;
	}

	generator = new StaticImage("../Images/RGB-Megaman.data");
	if (generator->initialise())
	{
		name = generator->getName().c_str();
		ui.generatorComboBox->addItem(name);
		m_mapGenerators[name] = generator;
	}

	generator = new StaticImage("../Images/RGB-RainbowSwirls.data");
	if (generator->initialise())
	{
		name = generator->getName().c_str();
		ui.generatorComboBox->addItem(name);
		m_mapGenerators[name] = generator;
	}

	generator = new StaticImage("../Images/BW-Dragon.data");
	if (generator->initialise())
	{
		name = generator->getName().c_str();
		ui.generatorComboBox->addItem(name);
		m_mapGenerators[name] = generator;
	}

	generator = new StaticImage("../Images/BW-RevisionLogo.data");
	if (generator->initialise())
	{
		name = generator->getName().c_str();
		ui.generatorComboBox->addItem(name);
		m_mapGenerators[name] = generator;
	}

	generator = new BounceImage();
	if (generator->initialise())
	{
		name = generator->getName().c_str();
		ui.generatorComboBox->addItem(name);
		m_mapGenerators[name] = generator;
	}

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

	// Black and white
	effect = new BlackAndWhite();
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
	QString name;
	Converter *converter = new Nearest();
	if (converter->initialise())
	{
		name = converter->getName().c_str();
		ui.converterComboBox->addItem(name);
		m_mapConverters[name] = converter;
	}

	converter = new FullBlock();
	if (converter->initialise())
	{
		name = converter->getName().c_str();
		ui.converterComboBox->addItem(name);
		m_mapConverters[name] = converter;
	}

	converter = new HalfBlock();
	if (converter->initialise())
	{
		name = converter->getName().c_str();
		ui.converterComboBox->addItem(name);
		m_mapConverters[name] = converter;
	}
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

void ConverterTester::applyEffect(RGBA *input, QImage &outputImage)
{
	// Find out which effect I am using
	QString name = ui.effectComboBox->currentText();
	Effect *effect = m_mapEffects[name];

	effect->run(input, (RGBA*)outputImage.bits());

	// Apply effect
	ui.afterImage->setPixmap(QPixmap::fromImage(outputImage));
}

void ConverterTester::applyConverter(RGBA *image)
{
	// Find out which converter I am using
	QString name = ui.converterComboBox->currentText();
	Converter *converter = m_mapConverters[name];

	QImage outputImage(640, 400, QImage::Format_RGBA8888);
	uchar* output = outputImage.bits();

	CHAR_INFO console[80 * 50];

	// Convert into console chars
	converter->convert(image, console);

	// Convert back into a bitmap for testing
	converter->convertBack(console, (RGBA*)output);

	// Apply effect
	ui.converterImage->setPixmap(QPixmap::fromImage(outputImage));
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

		// Record the current time as the start time we offset from
		m_StartTime = Timer::getCurrentTime();
	}
}

void ConverterTester::updateAnimation()
{
	static int count = 0;

	// Record start time to measure whole process time
	std::chrono::system_clock::time_point start = Timer::getCurrentTime();

	// Calculate the time duration
	float time = Timer::getDuration(m_StartTime)/1000.0f;

	// Create an image to write to later
	QImage	image(640,400, QImage::Format_RGBA8888);
	RGBA *imageRGBA = (RGBA*)image.bits();

	// GENERATOR CODE

	// Find out which generator I am using
	QString name = ui.generatorComboBox->currentText();
	Generator *generator = m_mapGenerators[name];

	// Perform the image creation 
	generator->run(time, imageRGBA);

	// Update the GUI with the new image
	ui.beforeImage->setPixmap(QPixmap::fromImage(image));

	// EFFECT CODE
	QImage effectImage(640, 400, QImage::Format_RGBA8888);
	uchar* effectOutput = effectImage.bits();

	if (ui.enableEffectCheckBox->isChecked())
	{
		applyEffect(imageRGBA, effectImage);
	}

	// CONVERTER CODE
	if (ui.enableConverterCheckBox->isChecked())
	{
		applyConverter((RGBA*)effectOutput);
	}

	// Update status bar to show MS frame time
	float ms = Timer::getDuration(start);
	std::stringstream ss;
	ss << "Frametime = " << ms << "ms";
	ss << " Time = " << time << " seconds";

	ui.statusBar->showMessage(QString(ss.str().c_str()));

	count++;
}

void ConverterTester::toggleZoom()
{
	if (m_ZoomedIn)
	{
		// Zoom out 
		ui.converterImage->setMinimumSize(QSize(640, 400));
		ui.converterImage->setScaledContents(false);
		ui.centralWidget->resize(QSize(100, 100));
		m_ZoomedIn = false;
	}
	else
	{
		ui.converterImage->setMinimumSize(QSize(1280, 800));
		ui.converterImage->setScaledContents(true);
		m_ZoomedIn = true;
	}
}