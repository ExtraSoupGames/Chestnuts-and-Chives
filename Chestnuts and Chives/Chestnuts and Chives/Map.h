#pragma once
#include <map>
#include <vector>
#include "Path.h"
#include "UIElement.h"
#include "GameManager.h"
using namespace std;
class Map : public UIElement
{
	vector<Path*> paths;
	vector<Location*> locations;
	SDL_Texture* backgroundTexture;
	int offsetX;
	int offsetY;
public:
	Map(int x , int y, GameManager* gameManager);
	virtual void Render(Renderer* renderer) override;
	//used for testing to move the map around
	void UpdateOffset();
};

