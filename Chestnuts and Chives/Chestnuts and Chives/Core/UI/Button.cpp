#include "Button.h"
Button::Button(string text, int x, int y, int width, int height, function<bool()> callOnClick, Client* manager)
	: Text(x, y, text, manager, width, height)
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

	//TODO button hover animations
	if (hovered) {
		renderer->DrawTexture(left, topLeftX, topLeftY, 16, 16, 1);
		renderer->DrawTexture(middle, topLeftX + 16, topLeftY, width - 32, 16, 1);
		renderer->DrawTexture(right, topLeftX + width - 16, topLeftY, 16, 16, 1);
	}
	else {
		renderer->DrawTexture(right, topLeftX, topLeftY, 16, 16, 1);
		renderer->DrawTexture(middle, topLeftX + 16, topLeftY, width - 32, 16, 1);
		renderer->DrawTexture(left, topLeftX + width - 16, topLeftY, 16, 16, 1);
	}
	Text::Render(renderer);


}
void Button::HoverStarted()
{
}
void Button::HoverEnded()
{
}
void Button::Clicked()
{
	onClick();
}