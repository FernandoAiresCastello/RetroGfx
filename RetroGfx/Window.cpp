#include <stdio.h>
#include <stdarg.h>
#include "Window.h"

Window::Window(Graphics* gr, int x, int y, int w, int h, int fgc, int bgc, bool border) :
	X(x), Y(y), Width(w), Height(h), ForeColor(fgc), BackColor(bgc), Border(border), Gr(gr)
{
}

Window::~Window()
{
}

void Window::Draw()
{
	if (Border)
		DrawWithBorder();
	else
		DrawWithoutBorder();
}

void Window::DrawWithBorder()
{
	// Draw top corner
	Gr->PutChar(WchTopLeft, X, Y, ForeColor, BackColor);
	Gr->PutChar(WchTopRight, X + Width + 1, Y, ForeColor, BackColor);
	for (int i = 0; i < Width; i++)
		Gr->PutChar(WchTop, X + i + 1, Y, ForeColor, BackColor);

	// Draw middle
	for (int row = 0; row < Height; row++)
	{
		Gr->PutChar(WchLeft, X, Y + row + 1, ForeColor, BackColor);

		for (int i = 0; i < Width; i++)
			Gr->PutChar(WchSpace, X + i + 1, Y + row + 1, ForeColor, BackColor);

		Gr->PutChar(WchRight, X + Width + 1, Y + row + 1, ForeColor, BackColor);
	}

	// Draw bottom corner
	Gr->PutChar(WchBottomLeft, X, Y + Height + 1, ForeColor, BackColor);
	Gr->PutChar(WchBottomRight, X + Width + 1, Y + Height + 1, ForeColor, BackColor);
	for (int i = 0; i < Width; i++)
		Gr->PutChar(WchBottom, X + i + 1, Y + Height + 1, ForeColor, BackColor);
}

void Window::DrawWithoutBorder()
{
	for (int row = 0; row < Height; row++)
		for (int col = 0; col < Width; col++)
			Gr->PutChar(WchSpace, X + col, Y + row, ForeColor, BackColor);
}

void Window::Print(int x, int y, const char* fmt, ...)
{
	char str[1024] = { 0 };
	va_list arg;
	va_start(arg, fmt);
	vsprintf_s(str, fmt, arg);
	va_end(arg);

	Print(x, y, ForeColor, BackColor, str);
}

void Window::Print(int x, int y, int forecolor, const char* fmt, ...)
{
	char str[1024] = { 0 };
	va_list arg;
	va_start(arg, fmt);
	vsprintf_s(str, fmt, arg);
	va_end(arg);

	Print(x, y, forecolor, BackColor, str);
}

void Window::Print(int x, int y, int forecolor, int backcolor, const char* fmt, ...)
{
	char str[1024] = { 0 };
	va_list arg;
	va_start(arg, fmt);
	vsprintf_s(str, fmt, arg);
	va_end(arg);

	if (Border)
	{
		x++;
		y++;
	}

	Gr->Print(X + x, Y + y, forecolor, backcolor, str);
}

void Window::PutChar(int chr, int x, int y)
{
	PutChar(chr, x, y, ForeColor, BackColor);
}

void Window::PutChar(int chr, int x, int y, int forecolor)
{
	PutChar(chr, x, y, forecolor, BackColor);
}

void Window::PutChar(int chr, int x, int y, int forecolor, int backcolor)
{
	if (Border)
	{
		x++;
		y++;
	}

	Gr->PutChar(chr, X + x, Y + y, forecolor, backcolor);
}
