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
	float textureWidth;
	float textureHeight;
	SDL_GetTextureSize(backgroundTexture, &textureWidth, &textureHeight);
	mapTextureWidth = textureWidth;
	mapTextureHeight = textureHeight;
}

void Map::Render(Renderer* renderer)
{
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
	//clamp offsetX between 0 and the textureWidth minus the display width
	offsetX = offsetX < 0 ? 0 : offsetX >(mapTextureWidth - width) ? (mapTextureWidth - width) : offsetX;
	//clamp offsetY between 0 and the textureHeight minus the display height
	offsetY = offsetY < 0 ? 0 : offsetY >(mapTextureHeight - height) ? (mapTextureHeight - height) : offsetY;
}