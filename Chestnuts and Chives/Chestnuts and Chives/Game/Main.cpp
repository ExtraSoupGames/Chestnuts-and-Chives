//Chestnuts and Chives
//Jonathan Collins

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_net/SDL_net.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "Client.h"
#include "Server.h"
#include "Renderer.h"
static SDL_Window* window = NULL;
static Client* playerClient;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    std::string gameName = "Chestnuts and Chives";
    std::string versionName = "0.3.6";

    SDL_SetAppMetadata(gameName.c_str(), versionName.c_str(), "com.extrasoup.games.chestnutsandchives");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDLNet_Init()) {
        SDL_Log("Couldn't initialize SDLNet: %s", SDL_GetError());
    }
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDLTtf: %s", SDL_GetError());
    }
    std::string windowName = gameName + " " + versionName;
    int z = 0;
    for (int i = 0; i < 99999999; i++) {
        z += i;
    }
    cout << "z is " << z << endl;
    int clientPort = SDL_GetTicks();
    cout << "Client port: " << clientPort << endl;
    playerClient = new Client(clientPort, windowName);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    playerClient->ManageInput(event);
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    playerClient->Update();
    playerClient->Render();
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    delete playerClient;
    /* SDL will clean up the window/renderer for us. */
}


