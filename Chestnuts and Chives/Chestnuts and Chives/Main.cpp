//Chestnuts and Chives
//Jonathan Collins

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_net/SDL_net.h>
#include <string>
#include "Client.h"
#include "Server.h"
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static Client* playerClient;
static Client* testingClient;
static Server* gameServer;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    std::string gameName = "Chestnuts and Chives";
    std::string versionName = "0.0.0";

    SDL_SetAppMetadata(gameName.c_str(), versionName.c_str(), "com.extrasoup.games.chestnutsandchives");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDLNet_Init()) {
        SDL_Log("Couldn't initialize SDLNet: %s", SDL_GetError());
    }
    std::string windowName = gameName + " " + versionName;
    if (!SDL_CreateWindowAndRenderer(windowName.c_str(), 640, 480, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    gameServer = new Server();
    playerClient = new Client(66662);
    testingClient = new Client(88888);
    playerClient->ConnectToServer("127.0.0.1");
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    //TODO implement input handling
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (testingClient->IsConnected()) {
            return SDL_APP_CONTINUE;  /* carry on with the program! */
        }
        testingClient->ConnectToServer("127.0.0.1");
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    gameServer->Update();
    playerClient->Update();
    testingClient->Update();
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}


