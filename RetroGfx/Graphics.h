#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL.h>

#define SCREEN_W 256
#define SCREEN_H 192
#define WINDOW_W (SCREEN_W * 3)
#define WINDOW_H (SCREEN_H * 3)
#define CHAR_W 8
#define CHAR_H 8
#define CHAR_SIZE (CHAR_W * CHAR_H)
#define CHARSET_SIZE 512
#define COLS (SCREEN_W / CHAR_W)
#define ROWS (SCREEN_H / CHAR_H)

#define CHARSET_FILE "charset.dat"

typedef unsigned char byte;

class Graphics
{
public:
	byte Charset[CHARSET_SIZE][CHAR_H];
	int Buffer[SCREEN_H][SCREEN_W];

	Graphics(int bgcolor, bool fullscreen);
	~Graphics();

	void ClearCharset();
	void SetupDefaultCharset();
	void ToggleFullscreen();
	void Update();
	void Clear(int color);
	void SetPixel(int x, int y, int color);
	void SetChar(int chr, int row1, int row2, int row3, int row4, int row5, int row6, int row7, int row8);
	void PutChar(int chr, int x, int y, int forecolor, int backcolor);
	void DrawChar(int chr, int x, int y, int forecolor, int backcolor);
	void Print(int x, int y, int forecolor, int backcolor, const char* fmt, ...);
	void SaveCharset(const char* filename);
	void LoadCharset(const char* filename);

private:
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	SDL_Texture* ScreenTexture;

	void Init(bool fullscreen);
	void Dispose();
};

#endif
