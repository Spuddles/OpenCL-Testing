#include "display.h"
#include <iostream>

Display::Display()
{
    _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    _ScreenSize.X = 80;
    _ScreenSize.Y = 50;

    _BufferCoord.X = 0;
    _BufferCoord.Y = 0;

    _WriteArea.Top = 0;
    _WriteArea.Left = 0;
    _WriteArea.Bottom = 49;
    _WriteArea.Right = 79;

    // Make sure the screen buffer is the correct 80*50 size
    if (SetConsoleScreenBufferSize(_hConsole, _ScreenSize)==FALSE)
    {
        std::cout << "Failed to set the screen buffer size" << std::endl;
    }

    SetConsoleTitle("Spud Testing App");
}

Display::~Display()
{
}

void Display::ClearBuffer()
{
    CHAR_INFO   ci;

    ci.Char.AsciiChar = ' ';
    ci.Attributes = 0;

    for (int i=0;i<80*50;i++)
    {
        _ScreenBuffer[i] = ci;
    }
}

void Display::FillBuffer(char ch, char attrib)
{
    CHAR_INFO   ci;

    ci.Char.AsciiChar = ch;
    ci.Attributes = attrib;

    for (int i=0;i<80*50;i++)
    {
        _ScreenBuffer[i] = ci;
    }
}

void Display::CopyToBuffer(char *data)
{
	for (int i = 0; i<80 * 50; i++)
	{
		_ScreenBuffer[i].Char.AsciiChar = *data++;
		_ScreenBuffer[i].Attributes = *data++;
	}
}

void Display::UpdateConsole()
{
    WriteConsoleOutput(_hConsole,_ScreenBuffer,_ScreenSize,_BufferCoord,&_WriteArea);
}

void Display::DisplayConsoleDetails()
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(_hConsole ,&info);
}

CHAR_INFO* Display::GetScreenBuffer()
{
    return reinterpret_cast<CHAR_INFO*>(&_ScreenBuffer);
}

void Display::SetChar(int x, int y, char ch, char attrib)
{
    CHAR_INFO ci;
    ci.Char.AsciiChar = ch;
    ci.Attributes = attrib;

    _ScreenBuffer[(y*80)+x] = ci;
}

void Display::DrawTestImage()
{
    for (int i=0;i<256;++i)
    {
        SetChar(i%16, i/16, i, 15);
    }
}

void Display::MoveCursor(unsigned int x, unsigned int y)
{
	COORD pos{ (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(_hConsole, pos);
}