#include "Text.h"

Text::Text(int x, int y, string text, Client* manager) : UIElement(x, y, 5, 5)
{
	font = manager->GetFont();
	displayText = text;
}

void Text::Render(Renderer* renderer)
{
	SDL_Color textColor = { 255, 0, 0, 255 }; // White color
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, displayText.c_str(), displayText.size(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer->GetRenderer() , textSurface);
	SDL_DestroySurface(textSurface);
	renderer->DrawTexture(textTexture, topLeftX, topLeftY, 100, 100);
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
