#include "Button.h"

Button::Button(int x, int y, int width, int height, function<bool()> callOnClick, GameManager* manager)
	: UIElement(x, y, width, height)
{
	isBlocking = false;
	isClickable = true;
	onClick = callOnClick;
	left = manager->GetTexture("UI/Left");
	right = manager->GetTexture("UI/Right");
	middle = manager->GetTexture("UI/Middle");
}

void Button::Render(Renderer* renderer)
{
	renderer->DrawTexture(left, topLeftX, topLeftY, 16, 16, 1);
	renderer->DrawTexture(middle, topLeftX + 16, topLeftY, 16, 16, 1);
	renderer->DrawTexture(right, topLeftX + 32, topLeftY, 16, 16, 1);
}
void Button::OnClick(SDL_Event* e)
{
}
