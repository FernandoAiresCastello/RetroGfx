#ifndef _CHARSELECTOR_H_
#define _CHARSELECTOR_H_

#include "Graphics.h"
#include "Window.h"

class CharSelector
{
public:
	CharSelector(Graphics* gr, int x, int y);
	~CharSelector();

	int Select(int initialChar);

private:
	Graphics* Gr;
	Window* Win;
	Window* WinInd;
	int CharIndex;
	bool Running;
	int X;
	int Y;

	CharSelector(CharSelector& other) {}

	void Draw();
	int GetFirstCharIndexInPage();
};

#endif
