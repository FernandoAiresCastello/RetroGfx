#ifndef _CHAREDITOR_H_
#define _CHAREDITOR_H_

#include "Graphics.h"
#include "Window.h"

class CharEditor
{
public:
	CharEditor(Graphics* gr, int x, int y);
	~CharEditor();

	int Edit(int charIndex);

private:
	Graphics* Gr;
	Window* Win;
	Window* WinPreview;
	Window* WinInd;
	int CharIndex;
	bool Running;
	int X;
	int Y;
	int PixelRow;
	int PixelBit;
	char Buffer[CHAR_SIZE];
	
	CharEditor(CharEditor& other) {}

	void SetCharIndex(int index);
	void FillBuffer();
	void UpdateChar();
	void Draw();
	char& GetCurrentPixel();
	void SetPixelOn();
	void SetPixelOff();
	void TogglePixel();
	void ClearChar();
};

#endif
