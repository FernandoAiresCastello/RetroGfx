#ifndef _BUFFEREDWINDOW_H_
#define _BUFFEREDWINDOW_H_

#include "Window.h"
#include "CharBuffer.h"

class BufferedWindow : public Window
{
public:
	CharBuffer* Buffer;

	BufferedWindow(Graphics* gr, int x, int y, int w, int h, int fgc, int bgc, 
		int bufferW, int bufferH, bool border = true);
	
	virtual ~BufferedWindow();

	virtual void Draw();
	virtual void Print(int x, int y, const char* fmt, ...);
	virtual void Print(int x, int y, int forecolor, const char* fmt, ...);
	virtual void Print(int x, int y, int forecolor, int backcolor, const char* fmt, ...);
	virtual void PutChar(int chr, int x, int y);
	virtual void PutChar(int chr, int x, int y, int forecolor);
	virtual void PutChar(int chr, int x, int y, int forecolor, int backcolor);
};

#endif
