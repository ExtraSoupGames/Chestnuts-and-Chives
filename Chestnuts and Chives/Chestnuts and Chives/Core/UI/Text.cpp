#include "Text.h"

Text::Text(int x, int y, string text, Client* manager) : UIElement(x, y, 5, 5)
{
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
