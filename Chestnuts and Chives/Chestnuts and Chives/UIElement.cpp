#include "UIElement.h"
void UIElement::Render(Renderer* renderer)
{
	renderer->DrawTexture(texture, topLeftX, topLeftY);
}

UIElement::UIElement(SDL_Texture* texture, int x, int y) : Renderable(texture)
{
	topLeftX = x;
	topLeftY = y;
}
