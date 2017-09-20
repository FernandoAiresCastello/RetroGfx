#include "Char.h"

Char::Char() : 
	Index(0), ForeColor(0), BackColor(0)
{
}

Char::Char(int ix, int fgc, int bgc) : 
	Index(ix), ForeColor(fgc), BackColor(bgc)
{
}

Char::Char(Char& other) : 
	Index(other.Index), ForeColor(other.ForeColor), BackColor(other.BackColor)
{
}

void Char::Clear()
{
	Index = 0;
	ForeColor = 0;
	BackColor = 0;
}
