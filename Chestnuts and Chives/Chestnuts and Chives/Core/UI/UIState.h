#pragma once
#include "GameState.h"
#include "UIElement.h"
#include <vector>
using namespace std;
class UIState : public GameState
{
private:
protected:
	int screenScaling;
	vector<UIElement*> elements;
	UIElement* GetHoveredElement();
public:
	~UIState();
	bool DoElementsOverlap();
	bool IsAllSpaceFilled();
	//when overriden this base method should still be called to render all UI elements
	virtual void Render(Renderer* renderer) override;
	//when overriden this base method should be called whenever an event is 100% not involved in the UI
	virtual void ManageInput(SDL_Event* e) override;
};