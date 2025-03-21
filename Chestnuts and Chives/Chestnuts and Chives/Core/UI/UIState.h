#pragma once
#include "GameState.h"
#include "UIElement.h"
#include <vector>
using namespace std;
class UIState : public GameState
{
private:
protected:
	vector<UIElement*> elements;
public:
	~UIState();
	bool DoElementsOverlap();
	bool IsAllSpaceFilled();
	//when overriden this base method should be called to render all UI elements
	virtual void Render(Renderer* renderer) override;
};

