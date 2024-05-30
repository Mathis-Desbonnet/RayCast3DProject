#include <stdio.h>
#include <SDL.h>
#include "SDLWindow.h"
#include "Player.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    int listOfBlock[10][10] = {{0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
                               {0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
                               {0, 1, 1, 0, 0, 1, 1, 1, 1, 0},
                               {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                               {0, 1, 1, 1, 0, 0, 0, 0, 1, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                               {1, 1, 0, 0, 1, 0, 0, 0, 0, 0},
                               {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
                               {1, 1, 0, 0, 0, 0, 0, 0, 0, 0}};
    Player* firstPlayer = createPlayer(200, 540, 180, 90);
    SDL_Rect playerRect = {firstPlayer->posX, firstPlayer->posY, 50, 50};
    SDL_Surface* playerImage = SDL_LoadBMP("playerImage.bmp");
    SDL_Window* SDLWindow;
    SDL_Renderer* SDLRenderer;
    SDL_Event newEvent;
    int running = 1;
    int speed = 3;
    int logSize = 0;
    float angle = 0;
    SDL_CreateWindowAndRenderer(1920, 1080, SDL_WINDOW_FULLSCREEN, &SDLWindow, &SDLRenderer);
    SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(SDLRenderer, playerImage);
    SDL_FreeSurface(playerImage);
    SDL_RenderSetVSync(SDLRenderer, 60);
    SDL_Rect* listOfRect = createAllRect(listOfBlock, &logSize);
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    SDL_FPoint viewPointForWalls = {100, 0};
    SDL_FPoint viewPointOfPlayer;
    while (running) {
        SDL_PollEvent(&newEvent);
        calculateAnglePointPlayer(firstPlayer, angle, 100, 0, 25, 0, &viewPointForWalls, &viewPointOfPlayer);
        if (SDL_QUIT == newEvent.type || keyState[SDL_GetScancodeFromKey(SDLK_ESCAPE)]) {
            SDLQuit(SDLWindow, SDLRenderer);
            running = 0;
        }
        if (keyState[SDL_GetScancodeFromKey(SDLK_a)]) {
            angle++;
            SDL_Log("oui\t angle : %f\t angle : %f\t cos : %f\t sin : %f\t posX, posY : %f %f",angle*PI/180, angle,cosf((angle*PI/180)), sinf(angle*PI/180), viewPointForWalls.x, viewPointForWalls.y);
        } else if (keyState[SDL_GetScancodeFromKey(SDLK_e)]) {
            angle--;
        }
        movePlayer(firstPlayer, speed, keyState, &playerRect, &viewPointForWalls, angle*PI/180);
        SDL_SetRenderDrawColor(SDLRenderer, 0, 0 ,0, 255);
        SDL_RenderClear(SDLRenderer);
        SDL_SetRenderDrawColor(SDLRenderer, 0, 0 ,255, 255);
        SDL_RenderFillRects(SDLRenderer, listOfRect, logSize);
        SDL_SetRenderDrawColor(SDLRenderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(SDLRenderer, &playerRect);
        SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 0, 255);
        SDL_RenderCopyEx(SDLRenderer, playerTexture, NULL, &playerRect, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderDrawLineF(SDLRenderer, viewPointOfPlayer.x, viewPointOfPlayer.y, viewPointForWalls.x+viewPointOfPlayer.x, viewPointForWalls.y+viewPointOfPlayer.y);
        SDL_RenderPresent(SDLRenderer);
        SDL_Delay(20);
    }
    free(listOfRect);
    listOfRect = NULL;
    return EXIT_SUCCESS;
}
