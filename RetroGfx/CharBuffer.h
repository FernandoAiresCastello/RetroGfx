#ifndef _CHARBUFFER_H_
#define _CHARBUFFER_H_

#include "Char.h"

class CharBuffer
{
public:
	Char* Buffer;
	int Width;
	int Height;
	int Size;

	CharBuffer(int width, int height);
	~CharBuffer();

	void Set(int x, int y, int ix, int fgc, int bgc);
	Char& Get(int x, int y);
	void Clear();
};

#endif
