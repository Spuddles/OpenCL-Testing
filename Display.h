#ifndef DISPLAY_H
#define DISPLAY_H

#undef UNICODE
#include <Windows.h>

class Display
{
public:
            Display();
            ~Display();

    void    ClearBuffer();
    void    FillBuffer(char ch, char attrib);
	void	CopyToBuffer(char *data);
    void    UpdateConsole();

    void    DisplayConsoleDetails();
    CHAR_INFO *GetScreenBuffer();

    void    SetChar(int x, int y, char ch, char attrib);
    void    DrawTestImage();
	void	MoveCursor(unsigned int x, unsigned int y);

private:

    // Hold the handle to the output console
    HANDLE      _hConsole;

    // Offscreen space used to store teh framebuffer
    CHAR_INFO   _ScreenBuffer[80*50];

    // Initialised to be the default size of the screen (80*50)
    COORD       _ScreenSize;

    // Offset into the buffer for updating the console (0,0)
    COORD       _BufferCoord;

    // Area of the buffer used to update the console ( 0,0 to 79,49 )
    SMALL_RECT  _WriteArea;


};

#endif // DISPLAY_H
