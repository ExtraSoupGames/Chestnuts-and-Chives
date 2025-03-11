#include "Location.h"
#include "GameManager.h"
Location::Location(GameManager* gameManager)
{
	locationTexture = gameManager->GetTexture("Location");
}

void Location::Render(Renderer* renderer, int mapX, int mapY, int mapWidth, int mapHeight, int offsetX, int offsetY)
{
	renderer->DrawTextureClipped(locationTexture, mapX, mapY, mapWidth, mapHeight, offsetX, offsetY);
}
