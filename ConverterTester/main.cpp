#include "convertertester.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ConverterTester w;

	w.show();
	return a.exec();
}
