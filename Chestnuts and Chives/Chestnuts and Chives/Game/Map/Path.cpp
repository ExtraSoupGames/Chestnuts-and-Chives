#include "Path.h"

Path::Path(GameManager* gameManager)
{
	pathTexture = gameManager->GetTexture("Paths");
}

void Path::Render(Renderer* renderer, int mapX, int mapY, int mapWidth, int mapHeight,  int offsetX, int offsetY)
{
	renderer->DrawTextureClipped(pathTexture, mapX, mapY, mapWidth, mapHeight, offsetX, offsetY);
}
