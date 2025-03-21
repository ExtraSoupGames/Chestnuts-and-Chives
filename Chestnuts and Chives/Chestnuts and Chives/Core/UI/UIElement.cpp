#include "UIElement.h"
UIElement::UIElement(int x, int y, int pWidth, int pHeight)
{
	topLeftX = x;
	topLeftY = y;
	width = pWidth;
	height = pHeight;
}

bool UIElement::ContainsMouse(int mouseX, int mouseY)
{
	if (!isClickable) {
		return false;
	}
	if (mouseX < topLeftX || mouseX > topLeftX + width) {
		return false;
	}
	if (mouseY < topLeftY || mouseY > topLeftY + height) {
		return false;
	}
	return true;
}
