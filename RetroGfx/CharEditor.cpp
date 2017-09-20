#include <SDL.h>
#include <string>
#include "CharEditor.h"
using namespace std;

#define FGC 0xffffff
#define BGC 0x000000
#define FGC_CURSOR 0x00ffff
#define BGC_CURSOR 0x0000ff

CharEditor::CharEditor(Graphics* gr, int x, int y) : 
	Gr(gr), CharIndex(0), Running(false), X(x), Y(y), PixelRow(0), PixelBit(0), Buffer()
{
	WinInd =     new Window(gr, x, y, 8, 1, FGC, BGC);
	Win =        new Window(gr, x, y + 3, CHAR_W, CHAR_H, FGC, BGC);
	WinPreview = new Window(gr, x, y + CHAR_H + 5, CHAR_W, 3, FGC, BGC);
}

CharEditor::~CharEditor()
{
	delete Win;
	delete WinPreview;
	delete WinInd;
}

int CharEditor::Edit(int charIndex)
{
	SetCharIndex(charIndex);
	Running = true;

	while (Running)
	{
		Draw();
		Gr->Update();

		SDL_Event e = { 0 };
		SDL_PollEvent(&e);

		if (e.type == SDL_KEYDOWN)
		{
			const byte* keys = SDL_GetKeyboardState(NULL);
			bool space = keys[SDL_SCANCODE_SPACE];

			switch (e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				case SDLK_RETURN:
				{
					Running = false;
					break;
				}
				case SDLK_PAGEUP:
				{
					if (CharIndex > 0)
					{
						UpdateChar();
						SetCharIndex(CharIndex - 1);
					}
					break;
				}
				case SDLK_PAGEDOWN:
				{
					if (CharIndex < CHARSET_SIZE - 1)
					{
						UpdateChar();
						SetCharIndex(CharIndex + 1);
					}
					break;
				}
				case SDLK_RIGHT:
				{
					if (PixelBit < CHAR_W - 1)
					{
						if (space) SetPixelOn();
						PixelBit++;
						if (space) SetPixelOn();
					}
					break;
				}
				case SDLK_LEFT:
				{
					if (PixelBit > 0)
					{
						if (space) SetPixelOn();
						PixelBit--;
						if (space) SetPixelOn();
					}
					break;
				}
				case SDLK_UP:
				{
					if (PixelRow > 0)
					{
						if (space) SetPixelOn();
						PixelRow--;
						if (space) SetPixelOn();
					}
					break;
				}
				case SDLK_DOWN:
				{
					if (PixelRow < CHAR_H - 1)
					{
						if (space) SetPixelOn();
						PixelRow++;
						if (space) SetPixelOn();
					}
					break;
				}
				case SDLK_SPACE:
				{
					TogglePixel();
					break;
				}
				case SDLK_DELETE:
				{
					ClearChar();
					break;
				}
			}
		}
	}

	UpdateChar();
	return CharIndex;
}

void CharEditor::SetCharIndex(int index)
{
	CharIndex = index;
	FillBuffer();
}

void CharEditor::FillBuffer()
{
	byte* pixels = Gr->Charset[CharIndex];
	int bufferIx = 0;

	for (int row = 0; row < CHAR_H; row++)
	{
		const unsigned int& bits = pixels[row];

		for (int pos = CHAR_W - 1; pos >= 0; pos--, bufferIx++)
		{
			int pixelOn = (bits & (1 << pos));
			Buffer[bufferIx] = pixelOn ? '1' : '0';
		}
	}
}

void CharEditor::UpdateChar()
{
	byte* pixels = Gr->Charset[CharIndex];

	for (int row = 0; row < CHAR_H; row++)
	{
		string rowbits = "";

		for (int col = 0; col < CHAR_W; col++)
			rowbits += Buffer[col + (row * CHAR_W)];

		pixels[row] = (byte)strtol(rowbits.c_str(), NULL, 2);
	}
}

void CharEditor::Draw()
{
	Win->Draw();
	WinPreview->Draw();
	WinInd->Draw();

	int initX = X + 1;
	int px = initX;
	int py = Y + 4;

	for (int row = 0; row < CHAR_H; row++)
	{
		for (int col = 0; col < CHAR_W; col++, px++)
		{
			int pixelOn = Buffer[col + (row * CHAR_W)] == '1';
			bool atCursor = PixelRow == row && PixelBit == col;

			int chr = 0x00;
			if (pixelOn || atCursor)
				chr = 0xdb;

			int color;
			if (atCursor)
			{
				if (pixelOn)
					color = FGC_CURSOR;
				else
					color = BGC_CURSOR;
			}
			else
				color = FGC;

			Gr->PutChar(chr, px, py, color, BGC);
		}

		py++;
		px = initX;
	}

	Gr->Print(WinInd->X + 2, WinInd->Y + 1, FGC, BGC, "%i", CharIndex);
	Gr->PutChar(CharIndex, WinInd->X + 7, WinInd->Y + 1, FGC, BGC);

	for (int mx = 0; mx < WinPreview->Width; mx++)
		for (int my = 0; my < WinPreview->Height; my++)
			Gr->PutChar(CharIndex, WinPreview->X + mx + 1, WinPreview->Y + my + 1, FGC, BGC);
}

char& CharEditor::GetCurrentPixel()
{
	return Buffer[PixelBit + (PixelRow * CHAR_W)];
}

void CharEditor::SetPixelOn()
{
	GetCurrentPixel() = '1';
	UpdateChar();
}

void CharEditor::SetPixelOff()
{
	GetCurrentPixel() = '0';
	UpdateChar();
}

void CharEditor::TogglePixel()
{
	char& c = GetCurrentPixel();

	if (c == '1')
		c = '0';
	else
		c = '1';

	UpdateChar();
}

void CharEditor::ClearChar()
{
	for (unsigned i = 0; i < CHAR_SIZE; i++)
		Buffer[i] = '0';

	UpdateChar();
}
