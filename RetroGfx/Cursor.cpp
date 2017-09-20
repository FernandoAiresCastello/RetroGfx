#include <SDL.h>
#include "Graphics.h"
#include "Cursor.h"

Cursor::Cursor(int minX, int minY, int maxX, int maxY, bool wrap) :
	X(minX), Y(minY), MinX(minX), MinY(minY), MaxX(maxX), MaxY(maxY), Wrap(wrap)
{
}

void Cursor::MoveUp()
{
	if (Y == MinY)
	{
		if (Wrap)
			Y = MaxY;
	}
	else
	{
		Y--;
	}
}

void Cursor::MoveDown()
{
	if (Y == MaxY)
	{
		if (Wrap)
			Y = MinY;
	}
	else
	{
		Y++;
	}
}

void Cursor::MoveRight()
{
	if (X == MaxX)
	{
		if (Wrap)
			X = MinX;
	}
	else
	{
		X++;
	}
}

void Cursor::MoveLeft()
{
	if (X == MinX)
	{
		if (Wrap)
			X = MaxX;
	}
	else
	{
		X--;
	}
}

void Cursor::MoveDist(int dx, int dy)
{
	X += dx;
	Y += dy;

	if (X < MinX)
		X = MinX;
	else if (X > MaxX)
		X = MaxX;
	if (Y < MinY)
		Y = MinY;
	else if (Y > MaxY)
		Y = MaxY;
}

void Cursor::Locate(int x, int y)
{
	if (x >= MinX && x <= MaxX && y >= MinY && y <= MaxY)
	{
		X = x;
		Y = y;
	}
}

void Cursor::SetBounds(int minX, int minY, int maxX, int maxY)
{
	MinX = minX;
	MinY = minY;
	MaxX = maxX;
	MaxY = maxY;
}

void Cursor::Home()
{
	Locate(MinX, MinY);
}

void Cursor::End()
{
	Locate(MaxX, MaxY);
}
