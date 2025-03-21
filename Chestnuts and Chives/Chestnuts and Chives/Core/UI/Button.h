#pragma once
#include "UIElement.h"
#include "SDL3/SDL.h"
#include <functional>
#include "GameManager.h"
using namespace std;
class Button : public UIElement {
private:
	SDL_Texture* left;
	SDL_Texture* right;
	SDL_Texture* middle;
protected:
	function<bool()> onClick;
public:
	//TODO pass in event callback to call when clicked
	Button(int x, int y, int width, int height, function<bool()> callOnClick, GameManager* manager);
	virtual void Render(Renderer* renderer) override;
	void OnClick(SDL_Event* e);
};