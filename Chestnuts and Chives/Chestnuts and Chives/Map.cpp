#include "Map.h"

Map::Map(int x, int y, GameManager* gameManager) : UIElement(x, y, 200, 160)
{
	backgroundTexture = gameManager->GetTexture("Map");
	offsetX = 0;
	offsetY = 0;
}

void Map::Render(Renderer* renderer)
{
	renderer->DrawTextureClipped(backgroundTexture, topLeftX, topLeftY, width, height, offsetX, offsetY);
	//TODO render map elements: paths and locations
}
void Map::UpdateOffset() {
	offsetX += 1;
	offsetY += 1;
	if (offsetX > 300) {
		offsetX = 0;
		offsetY = 0;
	}
}