#include "CharSelector.h"

#define FGC 0xffffff
#define BGC 0x000000
#define FGC_CURSOR 0x00ffff
#define BGC_CURSOR 0x0000ff
#define WIN_W 16
#define WIN_H 16
#define PAGE_SIZE 256

CharSelector::CharSelector(Graphics* gr, int x, int y) :
	Gr(gr), CharIndex(0), Running(false), X(x), Y(y)
{
	Win = new Window(gr, x, y, WIN_W, WIN_H, FGC, BGC);
	WinInd = new Window(gr, x + WIN_W + 2, y, 8, 1, FGC, BGC);
}

CharSelector::~CharSelector()
{
	delete Win;
	delete WinInd;
}

int CharSelector::Select(int initialChar)
{
	CharIndex = initialChar;
	Running = true;

	while (Running)
	{
		Draw();
		Gr->Update();

		SDL_Event e = { 0 };
		SDL_PollEvent(&e);

		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				{
					CharIndex = -1;
					Running = false;
					break;
				}
				case SDLK_RETURN:
				{
					Running = false;
					break;
				}
				case SDLK_RIGHT:
				{
					if (CharIndex < CHARSET_SIZE - 1)
						CharIndex++;
					break;
				}
				case SDLK_LEFT:
				{
					if (CharIndex > 0)
						CharIndex--;
					break;
				}
				case SDLK_UP:
				{
					if (CharIndex >= WIN_W)
						CharIndex -= WIN_W;
					break;
				}
				case SDLK_DOWN:
				{
					if (CharIndex < CHARSET_SIZE - WIN_W)
						CharIndex += WIN_W;
					break;
				}
				case SDLK_PAGEUP:
				{
					if (CharIndex >= PAGE_SIZE)
					{
						CharIndex -= PAGE_SIZE;
						CharIndex = GetFirstCharIndexInPage();
					}
					break;
				}
				case SDLK_PAGEDOWN:
				{
					if (CharIndex < CHARSET_SIZE - PAGE_SIZE)
					{
						CharIndex += PAGE_SIZE;
						CharIndex = GetFirstCharIndexInPage();
					}
					break;
				}
				case SDLK_HOME:
				{
					CharIndex = GetFirstCharIndexInPage();
					break;
				}
				case SDLK_END:
				{
					CharIndex = GetFirstCharIndexInPage() + PAGE_SIZE - 1;
					break;
				}
			}
		}
	}

	return CharIndex;
}

void CharSelector::Draw()
{
	Win->Draw();
	WinInd->Draw();

	int chr = (CharIndex / PAGE_SIZE) * PAGE_SIZE;

	for (int row = 0; row < WIN_H; row++)
	{
		for (int col = 0; col < WIN_W; col++, chr++)
		{
			bool atCursor = (CharIndex % PAGE_SIZE) == col + row * WIN_W;
			
			int fgc = FGC;
			int bgc = BGC;

			if (atCursor)
			{
				fgc = FGC_CURSOR;
				bgc = BGC_CURSOR;
			}

			Gr->PutChar(chr, col + X + 1, row + Y + 1, fgc, bgc);
		}
	}

	Gr->Print(WinInd->X + 2, WinInd->Y + 1, FGC, BGC, "%i", CharIndex);
	Gr->PutChar(CharIndex, WinInd->X + 7, WinInd->Y + 1, FGC, BGC);
}

int CharSelector::GetFirstCharIndexInPage()
{
	return (CharIndex / PAGE_SIZE) * PAGE_SIZE;
}
