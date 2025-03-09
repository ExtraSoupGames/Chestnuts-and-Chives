#include "UIElement.h"
void UIElement::Render(SDL_Renderer* renderer)
{
	SDL_RenderTexture(renderer, texture, NULL, NULL);
}

UIElement::UIElement(SDL_Texture* texture, int x, int y) : Renderable(texture)
{
	topLeftX = x;
	topLeftY = y;
}
