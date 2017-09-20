#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>
#include <vector>
using namespace std;

string Trim(string text);
vector<string> Split(string& text, char separator, bool trimTokens = true);
void Randomize();
int Random(int max);
bool RandomChance(int rate);
int Percent(int value, int percentage);
string Format(const char* fmt, ...);
int StrToInt(string str);
string IntToStr(int x);
void Pause(int ms = 1);
void WaitKey(int key);
void WaitAnyKey();

#endif
