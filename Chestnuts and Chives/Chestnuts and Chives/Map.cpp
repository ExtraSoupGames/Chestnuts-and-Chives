#include "Map.h"
#include "GameManager.h"
#include "Path.h"

Map::Map(int x, int y, GameManager* gameManager) : UIElement(x, y, 200, 160)
{
	backgroundTexture = gameManager->GetTexture("Map");
	offsetX = 0;
	offsetY = 0;
	paths.push_back(new Path(gameManager));
	locations.push_back(new Location(gameManager));
}

void Map::Render(Renderer* renderer)
{
	//TODO fix scaling issues due to map bounds exceeded
	renderer->DrawTextureClipped(backgroundTexture, topLeftX, topLeftY, width, height, offsetX, offsetY);
	for (int i = 0; i < locations.size();i++) {
		locations[i]->Render(renderer, topLeftX, topLeftY, width, height, offsetX, offsetY);
	}
	for (int i = 0; i < paths.size(); i++) {
		paths[i]->Render(renderer, topLeftX, topLeftY, width, height, offsetX, offsetY);
	}
}
void Map::UpdateOffset(int dX, int dY) {
	offsetX += dX;
	offsetY += dY;
	//TODO implement bounds
}