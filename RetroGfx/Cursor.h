#ifndef _CURSOR_H_
#define _CURSOR_H_

class Cursor
{
public:
	int X;
	int Y;
	int MinX;
	int MinY;
	int MaxX;
	int MaxY;
	bool Wrap;

	Cursor(int minX, int minY, int maxX, int maxY, bool wrap);

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void MoveDist(int dx, int dy);
	void Locate(int x, int y);
	void SetBounds(int minX, int minY, int maxX, int maxY);
	void Home();
	void End();
};

#endif
