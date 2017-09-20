#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Graphics.h"

class Window
{
public:
	int X;
	int Y;
	int Width;
	int Height;
	int ForeColor;
	int BackColor;
	bool Border;

	int WchSpace = 32;
	int WchTop = 196;
	int WchBottom = 196;
	int WchLeft = 179;
	int WchRight = 179;
	int WchTopLeft = 218;
	int WchTopRight = 191;
	int WchBottomLeft = 192;
	int WchBottomRight = 217;

	Window(Graphics* gr, int x, int y, int w, int h, int fgc, int bgc, bool border = true);
	virtual ~Window();

	virtual void Draw();
	virtual void Print(int x, int y, const char* fmt, ...);
	virtual void Print(int x, int y, int forecolor, const char* fmt, ...);
	virtual void Print(int x, int y, int forecolor, int backcolor, const char* fmt, ...);
	virtual void PutChar(int chr, int x, int y);
	virtual void PutChar(int chr, int x, int y, int forecolor);
	virtual void PutChar(int chr, int x, int y, int forecolor, int backcolor);

protected:
	Graphics* Gr;

	void DrawWithBorder();
	void DrawWithoutBorder();
};

#endif
