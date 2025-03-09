#pragma once
#include "GameState.h"
#include "UIElement.h"
#include <vector>
using namespace std;
class UIState : public GameState
{
private:
	vector<UIElement*> elements;
public:
	bool DoElementsOverlap();
	bool IsAllSpaceFilled();
	void Render(SDL_Renderer* renderer) override;
};

