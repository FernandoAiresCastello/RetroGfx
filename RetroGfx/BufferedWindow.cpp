#include "BufferedWindow.h"

BufferedWindow::BufferedWindow(
	Graphics* gr, int x, int y, int w, int h, int fgc, int bgc, int bufferW, int bufferH, bool border) :
	Window(gr, x, y, w, h, fgc, bgc, border), Buffer(new CharBuffer(bufferW, bufferH))
{
}

BufferedWindow::~BufferedWindow()
{
	delete Buffer;
}

void BufferedWindow::Draw()
{
}

void BufferedWindow::Print(int x, int y, const char* fmt, ...)
{
}

void BufferedWindow::Print(int x, int y, int forecolor, const char* fmt, ...)
{
}

void BufferedWindow::Print(int x, int y, int forecolor, int backcolor, const char* fmt, ...)
{
}

void BufferedWindow::PutChar(int chr, int x, int y)
{
}

void BufferedWindow::PutChar(int chr, int x, int y, int forecolor)
{
}

void BufferedWindow::PutChar(int chr, int x, int y, int forecolor, int backcolor)
{
}
