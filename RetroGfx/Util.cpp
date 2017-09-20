#include <SDL.h>
#include <stdarg.h>
#include <time.h>
#include "Util.h"

#define FMT_TO_STR_MAXLEN 1024

string Trim(string text)
{
	text.erase(0, text.find_first_not_of(' '));
	text.erase(text.find_last_not_of(' ') + 1);
	return text;
}

vector<string> Split(string& text, char separator, bool trimTokens)
{
	vector<string> tokens;
	string word;

	for (unsigned i = 0; i < text.length(); i++)
	{
		char character = text[i];

		if (character == separator)
		{
			if (trimTokens)
				word = Trim(word);

			tokens.push_back(word);
			word.clear();
		}
		else
			word += character;
	}

	if (trimTokens)
		word = Trim(word);

	tokens.push_back(word);

	return tokens;
}

void Randomize()
{
	srand((unsigned int)time(NULL));
}

int Random(int max)
{
	max++;

	static unsigned long long seed = 0;
	unsigned long long value;

	if (seed == 0)
		seed = time(NULL) + clock();

	seed = seed * 1664525 + 1013904223;
	value = (seed & 0xFFFFFFFF) * max / 0xFFFFFFFF;

	return (unsigned int)value;
}

bool RandomChance(int rate)
{
	if (rate >= 100)
		return true;
	if (rate > 0)
		return Random(100) <= rate;

	return false;
}

int Percent(int value, int percentage)
{
	return value * percentage / 100;
}

string Format(const char* fmt, ...)
{
	char str[FMT_TO_STR_MAXLEN] = { 0 };
	va_list arg;
	va_start(arg, fmt);
	vsprintf_s(str, fmt, arg);
	va_end(arg);

	return str;
}

int StrToInt(string str)
{
	return atoi(str.c_str());
}

string IntToStr(int x)
{
	return Format("%i", x);
}

void Pause(int ms)
{
	SDL_Delay(ms);
}

void WaitKey(int key)
{
	while (true)
	{
		SDL_Event e = { 0 };
		SDL_WaitEvent(&e);
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == key)
			break;
	}
}

void WaitAnyKey()
{
	while (true)
	{
		SDL_Event e = { 0 };
		SDL_WaitEvent(&e);
		if (e.type == SDL_KEYDOWN)
			break;
	}
}
