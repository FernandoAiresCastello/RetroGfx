#ifndef _CHARSELECTOREDITOR_H_
#define _CHARSELECTOREDITOR_H_

#include "Graphics.h"
#include "CharEditor.h"
#include "CharSelector.h"

class CharSelectorEditor
{
public:
	CharSelectorEditor(Graphics* gr, int intialChar);

	void Run();

private:
	Graphics* Gr;
	int CharIndex;
};

#endif
