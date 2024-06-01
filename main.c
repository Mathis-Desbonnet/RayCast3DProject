#include <stdio.h>
#include <SDL.h>
#include "SDLWindow.h"
#include "Player.h"
#include "algoBresenham.h"

#define SIZE 24

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    int listOfBlock[SIZE][SIZE] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,3,0,3,0,3,0,0,0,1},
            {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,3,0,0,0,3,0,0,0,1},
            {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,3,0,3,0,3,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
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
    int i;
    SDL_CreateWindowAndRenderer(1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP, &SDLWindow, &SDLRenderer);
    SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(SDLRenderer, playerImage);
    SDL_FreeSurface(playerImage);
    SDL_RenderSetVSync(SDLRenderer, 60);
    SDL_Rect* listOfRect = createAllRect(listOfBlock, &logSize);
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    SDL_FPoint viewPointForWalls = {3000, 0};
    SDL_FPoint viewPointOfPlayer;
    SDL_Point listOfPoint[360];
    SDL_Rect newRect;
    newRect.y = 0;
    newRect.w = 1920/90;
    newRect.h = 1080;

    int view2D = 1;
    int hasChanged = 0;
    while (running) {

        //2D Running

        SDL_PollEvent(&newEvent);
        if (SDL_QUIT == newEvent.type || keyState[SDL_GetScancodeFromKey(SDLK_ESCAPE)]) {
            SDLQuit(SDLWindow, SDLRenderer);
            running = 0;
        }
        if (keyState[SDL_GetScancodeFromKey(SDLK_TAB)]) {
            if (hasChanged == 0) {
                view2D = !view2D;
            }
            hasChanged++;
            if (hasChanged == 3) {
                hasChanged = 0;
            }
            SDL_Delay(10);
        }
        SDL_SetRenderDrawColor(SDLRenderer, 0, 0 ,0, 255);
        SDL_RenderClear(SDLRenderer);
        calculateAnglePointPlayer(firstPlayer, angle, 1920, 0, 25, 0, &viewPointForWalls, &viewPointOfPlayer);
        i = 0;
        for (int j = -45; j <= 45; j++) {
            DDA(viewPointOfPlayer.x, viewPointOfPlayer.y, ((cosf(((angle-j) * PI / 180)) * 1920)+viewPointOfPlayer.x)/(1920/SIZE), ((sinf((angle-j) * PI / 180) * 1920)+viewPointOfPlayer.y)/(1080/SIZE), listOfBlock, (int) angle + j, SDLRenderer, &listOfPoint[i++]);
        }
        movePlayer(firstPlayer, speed, keyState, &playerRect, &viewPointForWalls, angle*PI/180);
        changeAngle(&angle, keyState);

        if (view2D) { //2D Graphics
            SDL_SetRenderDrawColor(SDLRenderer, 0, 0 ,255, 255);
            SDL_RenderFillRects(SDLRenderer, listOfRect, logSize);

            SDL_SetRenderDrawColor(SDLRenderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(SDLRenderer, &playerRect);
            SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 0, 255);
            SDL_RenderCopyEx(SDLRenderer, playerTexture, NULL, &playerRect, angle, NULL, SDL_FLIP_NONE);
            SDL_SetRenderDrawColor(SDLRenderer, 0, 255, 0, 255);
            for (i = 0; i<90;i++) {
                if (!(listOfPoint[i].x > 1920 || listOfPoint[i].x < 0 || listOfPoint[i].y < 0 || listOfPoint[i].y > 1080)) {
                    SDL_RenderDrawLine(SDLRenderer, viewPointOfPlayer.x, viewPointOfPlayer.y, listOfPoint[i].x, listOfPoint[i].y);
                }
            }
        } else { //3D Graphics
            SDL_SetRenderDrawColor(SDLRenderer, 0, 255, 0, 255);
            for (i = 0; i < 90;i++) {
                newRect.x = (1920/90)*i;
                newRect.h = (SIZE*SIZE*1080)/((distance(viewPointOfPlayer.x, viewPointOfPlayer.y, listOfPoint[i].x, listOfPoint[i].y)*5));
                if (newRect.h > 1080) {
                    newRect.h = 1080;
                }
                newRect.y = 540-newRect.h/2;
                SDL_SetRenderDrawColor(SDLRenderer, 0, 255, 0, 255);
                SDL_RenderFillRect(SDLRenderer, &newRect);
            }
        }

        SDL_RenderPresent(SDLRenderer);

        SDL_Delay(20);
    }
    free(listOfRect);
    return EXIT_SUCCESS;
}
