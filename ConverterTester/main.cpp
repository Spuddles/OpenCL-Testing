#include "convertertester.h"
#include <QtWidgets/QApplication>

#include "../Utils/Utils.h"

/*
 * Function to turn the 16*16 tile charset into a 1*256 version for easier use
void temp()
{
	// Load the charset bitmap
	char *input = Utils::loadBinaryFile("..\\Images\\Charset.data");

	// Write it out in the char order
	char output[8*8*256] = { 0 };

	char* outputPtr = &output[0];
	for (int a = 0; a < 16; a++)
	{
		for (int b = 0; b < 16; b++)
		{
			// Find the start of the char we want to extract
			char* temp = input + (a * 16 * 8 * 8) + (b * 8);
			for (int y = 0; y < 8; y++)
			{
				for (int x = 0; x < 8; x++)
				{
					*(outputPtr++) = *(temp++);
				}
				temp += (15 * 8);
			}
		}
	}

	Utils::saveBinaryFile("..\\Images\\Charset-ordered.data", (char*)&output, sizeof(output));
}*/

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ConverterTester w;

	w.show();
	return a.exec();
}
