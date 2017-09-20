#include "CharSelectorEditor.h"

CharSelectorEditor::CharSelectorEditor(Graphics* gr, int initialChar) :
	Gr(gr), CharIndex(initialChar)
{
}

void CharSelectorEditor::Run()
{
	const int X = 2;
	const int Y = 3;

	while (CharIndex >= 0)
	{
		Gr->Clear(0);

		CharSelector* chrsel = new CharSelector(Gr, X, Y);
		CharIndex = chrsel->Select(CharIndex);
		delete chrsel;

		if (CharIndex >= 0)
		{
			CharEditor* chredit = new CharEditor(Gr, X + 18, Y);
			CharIndex = chredit->Edit(CharIndex);
			delete chredit;
		}
	}

	Gr->SaveCharset(CHARSET_FILE);
}
