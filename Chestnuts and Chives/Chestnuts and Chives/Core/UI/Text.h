#pragma once
#include "UIElement.h"
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "Client.h"
#include "SDL3/SDL_Render.h"
#include <iostream>
class GameManager;
using namespace std;
class Text : public UIElement {
private:
	TTF_Text* displayText;
protected:
public:
	Text(int x, int y, string text, Client* manager, int maxWidth = 150, int maxHeight = 50);
	virtual void Render(Renderer* renderer) override;
	virtual void HoverStarted() override;
	virtual void HoverEnded() override;
	virtual void Clicked() override;
};