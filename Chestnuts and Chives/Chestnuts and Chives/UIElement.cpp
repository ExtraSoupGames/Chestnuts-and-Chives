#include "UIElement.h"
void UIElement::Render(Renderer* renderer)
{
	renderer->DrawTexture(texture, topLeftX, topLeftY, width, height);
}

UIElement::UIElement(SDL_Texture* texture, int x, int y, int pWidth, int pHeight) : Renderable(texture)
{
	topLeftX = x;
	topLeftY = y;
	width = pWidth;
	height = pHeight;
}
