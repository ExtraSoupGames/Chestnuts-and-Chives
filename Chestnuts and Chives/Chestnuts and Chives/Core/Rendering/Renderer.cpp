#include "Renderer.h"

Renderer::Renderer(string windowName)
{
    renderer = NULL;
    window = NULL;
    resolution = RES_1280X720;
    const int screenWidth = (int)resolution * 320;
    const int screenHeight = (int)resolution * 180;
    if (!SDL_CreateWindowAndRenderer(windowName.c_str(), screenWidth, screenHeight, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return;
    }
    SDL_SetRenderScale(renderer, (int)resolution, (int)resolution);
}

void Renderer::UpdateScreen()
{
    SDL_RenderPresent(renderer);
}

void Renderer::FillBackground(SDL_Color* color)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderClear(renderer);
}
void Renderer::DrawTexture(SDL_Texture* texture, int x, int y, int width, int height, float opacity)
{
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureAlphaModFloat(texture, opacity);
    SDL_RenderTexture(renderer, texture, NULL, new SDL_FRect{(float)x, (float)y, (float)width, (float)height});
}
void Renderer::DrawTextureClipped(SDL_Texture* texture, int drawAreaX, int drawAreaY, int drawAreaWidth, int drawAreaHeight, int textureOffsetX, int textureOffsetY, float opacity) {
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureAlphaModFloat(texture, opacity);
    int textureScaling = (int)resolution;
    SDL_RenderTexture(renderer, texture,
        new SDL_FRect{(float)(textureOffsetX), (float)(textureOffsetY), (float)(drawAreaWidth), (float)(drawAreaHeight) },
        new SDL_FRect{ (float)drawAreaX, (float)drawAreaY, (float)drawAreaWidth, (float)drawAreaHeight });
}

int Renderer::GetScreenScalingFactor()
{
    return (int)resolution;
}

SDL_Texture* Renderer::LoadTextureFromSurface(SDL_Surface* surface)
{
    return SDL_CreateTextureFromSurface(renderer, surface);
}
