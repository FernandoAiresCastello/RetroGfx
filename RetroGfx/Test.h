#ifndef _TEST_H_
#define _TEST_H_

#include <string>
#include "Graphics.h"
using namespace std;

class Test
{
public:
	Test();
	~Test();

	void T1();
	void T2();
	void T3();
	void T4();
	void T5();

private:
	Graphics* Gr;

	const int C_FGC = 0xffffff;
	const int C_BGC = 0x000000;

	int Map[ROWS][COLS] = { 0 };
	int PlayerX = 15;
	int PlayerY = 10;

	void SetMap(string data);
};

#endif
