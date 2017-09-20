#ifndef _CHAR_H_
#define _CHAR_H_

class Char
{
public:
	int Index;
	int ForeColor;
	int BackColor;

	Char();
	Char(int ix, int fgc, int bgc);
	Char(Char& other);

	void Clear();
};

#endif
