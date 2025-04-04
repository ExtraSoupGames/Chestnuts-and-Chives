#include "Text.h"

Text::Text(int x, int y, string text, Client* manager, int maxWidth = 150, int maxHeight = 50) : UIElement(x, y, maxWidth, maxHeight)
{
	for (auto& x : text) {
		x = (char)toupper(x);
	}
	displayText = manager->GetRenderer()->CreateText(text);
}

void Text::Render(Renderer* renderer)
{

	renderer->DrawText(displayText, topLeftX, topLeftY);
}

void Text::HoverStarted()
{
}

void Text::HoverEnded()
{
}

void Text::Clicked()
{
}
