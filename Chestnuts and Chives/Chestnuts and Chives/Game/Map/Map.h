#pragma once
#include <map>
#include <vector>
#include "Location.h"
#include "UIElement.h"
using namespace std;
class GameManager;
class Path;
class Map : public UIElement
{
	vector<Path*> paths;
	vector<Location*> locations;
	SDL_Texture* backgroundTexture;
	int offsetX;
	int offsetY;
	int mapTextureWidth;
	int mapTextureHeight;
public:
	Map(int x , int y, GameManager* gameManager);
	virtual void Render(Renderer* renderer) override;
	//used for testing to move the map around
	void UpdateOffset(int dX, int dY);

	virtual void HoverStarted() override;
	virtual void HoverEnded() override;
	virtual void Clicked() override;
};

