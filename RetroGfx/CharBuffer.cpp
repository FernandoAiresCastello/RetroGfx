#include "CharBuffer.h"

CharBuffer::CharBuffer(int width, int height) : 
	Width(width), Height(height), Size(width * height)
{
	Buffer = new Char[width * height];

	Clear();
}

CharBuffer::~CharBuffer()
{
	delete[] Buffer;
}

void CharBuffer::Set(int x, int y, int ix, int fgc, int bgc)
{
	Buffer[y * Width + x] = Char(ix, fgc, bgc);
}

Char& CharBuffer::Get(int x, int y)
{
	return Buffer[y * Width + x];
}

void CharBuffer::Clear()
{
	for (int i = 0; i < Size; i++)
		Buffer[i].Clear();
}
