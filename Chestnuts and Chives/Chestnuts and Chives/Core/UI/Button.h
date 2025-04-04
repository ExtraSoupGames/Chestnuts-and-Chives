#pragma once
#include "UIElement.h"
#include "SDL3/SDL.h"
#include <functional>
#include "Client.h"
#include "Text.h"
class GameManager;
using namespace std;
class Button : public Text {
private:
	SDL_Texture* left;
	SDL_Texture* right;
	SDL_Texture* middle;
protected:
	function<bool()> onClick;
public:
	Button(string text, int x, int y, int width, int height, function<bool()> callOnClick, Client* manager);
	virtual void Render(Renderer* renderer) override;
	virtual void HoverStarted() override;
	virtual void HoverEnded() override;
	virtual void Clicked() override;
};