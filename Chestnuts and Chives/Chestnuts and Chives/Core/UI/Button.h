#pragma once
#include "UIElement.h"
#include "SDL3/SDL.h"
#include <functional>
class GameManager;
using namespace std;
class Button : public UIElement {
private:
	SDL_Texture* left;
	SDL_Texture* right;
	SDL_Texture* middle;
protected:
	function<bool()> onClick;
public:
	Button(int x, int y, int width, int height, function<bool()> callOnClick, GameManager* manager);
	virtual void Render(Renderer* renderer) override;
	virtual void HoverStarted() override;
	virtual void HoverEnded() override;
	virtual void Clicked() override;
};