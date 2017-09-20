#include <SDL.h>
#include "Test.h"
#include "Util.h"
#include "Window.h"
#include "CharEditor.h"
#include "CharSelector.h"
#include "CharSelectorEditor.h"
#include "CharBuffer.h"

void Test::T5()
{
	CharBuffer buffer(COLS, ROWS);

	buffer.Set(0, 0, '@', 0xff0000, 0xffff00);
	buffer.Set(buffer.Width-1, buffer.Height-1, '#', 0xff00ff, 0x0000ff);

	for (int y = 0; y < buffer.Height; y++)
	{
		for (int x = 0; x < buffer.Width; x++)
		{
			Char& ch = buffer.Get(x, y);
			Gr->PutChar(ch.Index, x, y, ch.ForeColor, ch.BackColor);
		}
	}

	Gr->Update();
	WaitAnyKey();
}

void Test::T4()
{
	const int bgc = 0x00ffff;
	PlayerX = 100;
	PlayerY = 100;

	bool running = true;
	while (running)
	{
		Gr->Clear(bgc);
		Gr->DrawChar(0xdb, PlayerX, PlayerY, 0xff0000, bgc);
		Gr->Update();

		SDL_PumpEvents();
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_SCANCODE_RIGHT])
			PlayerX++;
		if (keys[SDL_SCANCODE_LEFT])
			PlayerX--;
		if (keys[SDL_SCANCODE_DOWN])
			PlayerY++;
		if (keys[SDL_SCANCODE_UP])
			PlayerY--;
		if (keys[SDL_SCANCODE_ESCAPE])
			running = false;
		if (keys[SDL_SCANCODE_RETURN])
			Gr->ToggleFullscreen();
	}
}

void Test::T3()
{
	Window* w1 = new Window(Gr, 0, 0, 15, 10, 0xffffff, 0x800040, true);
	Window* w2 = new Window(Gr, 5, 5, 15, 10, 0xffffff, 0x400080, false);
	Window* w3 = new Window(Gr, 1, 20, 1, 1, 0xffffff, 0x008040, true);

	w1->Draw();
	w1->Print(0, 0, 0xffff00, "Hello World 1!");
	w2->Draw();
	w2->Print(0, 0, 0xff0000, 0xffffff, "Hello World 2!");
	w3->Draw();
	w3->PutChar('@', 0, 0, 0xff0000, 0xffff00);

	Gr->Update();

	WaitAnyKey();

	delete w1;
	delete w2;
	delete w3;
}

void Test::T2()
{
	const int bgc = 0xffff00;
	Gr->Clear(bgc);

	SetMap
	(
		"00000000000000000000000000000000"
		"00000000000000000000000000000000"
		"00000000000000000000001000000000"
		"00000000000000000000011100000000"
		"00000000000000000000111110000000"
		"00000000000000000001111111000000"
		"00000000000000000000110110000000"
		"00000000000000000000110110000000"
		"00000000000000000000000000000000"
		"00000000000000000000000000000000"
		"00000000000000000000000000000000"
		"00000000000000000000000000000000"
		"00000000000000000000000000000000"
		"00000000000000000000000000000000"
		"00000000000000000000000000000000"
		"00000000000000000000000000000000"
		"00000000000000000000000000000000"
		"00000000000000000000000000000000"
		"00001101010110000000000000000000"
		"00000111111100000000000000000000"
		"00000111011100000000000000000000"
		"00000111011100000000000000000000"
		"00000000000000000000000000000000"
		"00000000000000000000000000000000"
	);

	bool running = true;

	while (running)
	{
		for (int y = 0; y < ROWS; y++)
			for (int x = 0; x < COLS; x++)
				Gr->PutChar(Map[y][x], x, y, 0xff0000, bgc);

		Gr->PutChar(0xdb, PlayerX, PlayerY, 0x00ff00, bgc);
		Gr->Update();

		SDL_Event e = { 0 };
		SDL_PollEvent(&e);

		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				if (Map[PlayerY - 1][PlayerX] == 0)
					PlayerY--;
				break;
			case SDLK_DOWN:
				if (Map[PlayerY + 1][PlayerX] == 0)
					PlayerY++;
				break;
			case SDLK_LEFT:
				if (Map[PlayerY][PlayerX - 1] == 0)
					PlayerX--;
				break;
			case SDLK_RIGHT:
				if (Map[PlayerY][PlayerX + 1] == 0)
					PlayerX++;
				break;
			case SDLK_ESCAPE:
				running = false;
				break;
			case SDLK_RETURN:
				Gr->ToggleFullscreen();
				break;
			}
		}
	}
}

void Test::SetMap(string data)
{
	int x = 0;
	int y = 0;
	int val = 0;

	for (unsigned i = 0; i < data.length(); i++)
	{
		switch (data[i])
		{
		case '0': val = 0; break;
		case '1': val = 0xdb; break;
		}

		Map[y][x] = val;

		x++;
		if (x >= COLS)
		{
			x = 0;
			y++;
		}
	}
}

void Test::T1()
{
	CharSelectorEditor* ed = new CharSelectorEditor(Gr, 0);
	ed->Run();

	delete ed;
}

Test::Test()
{
	Gr = new Graphics(C_BGC, false);
}

Test::~Test()
{
	delete Gr;
}
