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
            {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
            {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
            {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,0,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    int firstTexture[] = { 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

                           0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
                           0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
                           1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0};
    Player* firstPlayer = createPlayer(200, 540, 180, 90);
    SDL_Rect playerRect = {firstPlayer->posX, firstPlayer->posY, 50, 50};
    SDL_Surface* playerImage = SDL_LoadBMP("playerImage.bmp");
    SDL_Window* SDLWindow;
    SDL_Renderer* SDLRenderer;
    SDL_Event newEvent;
    SDL_CreateWindowAndRenderer(1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP, &SDLWindow, &SDLRenderer);
    int running = 1;
    int speed = 3;
    int logSize = 0;
    int angle = 0;
    int i;
    int z = 0;
    SDL_Surface* allImageLoad[8] = {SDL_LoadBMP("src/bluestone.bmp"), SDL_LoadBMP("src/colorstone.bmp"), SDL_LoadBMP("src/eagle.bmp"), SDL_LoadBMP("src/greystone.bmp"), SDL_LoadBMP("src/mossy.bmp"), SDL_LoadBMP("src/purplestone.bmp"), SDL_LoadBMP("src/redbrick.bmp"), SDL_LoadBMP("src/wood.bmp")};
    SDL_Texture* allTextureImage[8];
    uint32_t* pixels[8];
    for (int j = 0; j<8; j++) {
        allTextureImage[j] = SDL_CreateTextureFromSurface(SDLRenderer, allImageLoad[j]);
        SDL_FreeSurface(allImageLoad[j]);
        pixels[j] = (uint32_t*) allImageLoad[j]->pixels;
    }
    SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(SDLRenderer, playerImage);
    SDL_FreeSurface(playerImage);
    SDL_RenderSetVSync(SDLRenderer, 60);
    SDL_Rect* listOfRect = createAllRect(listOfBlock, &logSize);
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    SDL_FPoint viewPointForWalls = {3000, 0};
    SDL_FPoint viewPointOfPlayer;
    SDL_FPoint listOfPoint[360];
    SDL_Rect newRect;
    SDL_Rect skyRect;
    SDL_Rect floorRect;
    newRect.y = 0;
    newRect.w = 1920/90;
    newRect.h = 1080;
    skyRect.y = 0;
    skyRect.w = 1920/90;
    skyRect.h = 1080;
    floorRect.y = 0;
    floorRect.w = 1920/90;
    floorRect.h = 1080;

    int view2D = 1;
    int hasChanged = 0;

    int typeOfWall[90];

    float ca[90];
    float ty, tyStep;
    int color;
    SDL_Rect drawingRectangle;
    drawingRectangle.w = 1920/90;

    while (running) {

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
        if (keyState[SDL_GetScancodeFromKey(SDLK_w)]) {
            if (z > -1000) {
                z -= 10;
            }
        }
        if (keyState[SDL_GetScancodeFromKey(SDLK_x)]) {
            if (z < 1000) {
                z += 10;
            }
        }
        SDL_SetRenderDrawColor(SDLRenderer, 0, 0 ,0, 255);
        SDL_RenderClear(SDLRenderer);
        calculateAnglePointPlayer(firstPlayer, angle, 1920, 0, 25, 0, &viewPointForWalls, &viewPointOfPlayer);
        DDA(viewPointOfPlayer.x, viewPointOfPlayer.y, firstPlayer->posX+25, firstPlayer->posY+25, listOfBlock, angle, SDLRenderer, listOfPoint, typeOfWall, ca, firstTexture);
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
                SDL_RenderDrawLineF(SDLRenderer, firstPlayer->posX+25, firstPlayer->posY+25, listOfPoint[i].x, listOfPoint[i].y);
            }
        } else { //3D Graphics
            for (i = 0; i < 90;i++) {
                newRect.x = (1920/90)*i;
                newRect.h = (SIZE*SIZE*1080)/((distance(viewPointOfPlayer.x, viewPointOfPlayer.y, listOfPoint[i].x, listOfPoint[i].y))*cos(ca[i]*PI/180)*3);
                newRect.y = 540-newRect.h/2+z;
                skyRect.y = 0;
                skyRect.h = newRect.y;
                skyRect.x = (1920/90)*i;
                floorRect.x = (1920/90)*i;
                floorRect.y = newRect.h+newRect.y;
                floorRect.h = 1080-floorRect.y;
                SDL_SetRenderDrawColor(SDLRenderer, 3, 182, 252, 255);
                SDL_RenderFillRect(SDLRenderer, &skyRect);
                SDL_SetRenderDrawColor(SDLRenderer, 207, 181, 161, 255);
                SDL_RenderFillRect(SDLRenderer, &floorRect);
                switch (typeOfWall[i]) {
                    case 1 :
                        SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 255, 255);
                        break;
                    case 2 :
                        SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);
                        break;
                    case 3 :
                        SDL_SetRenderDrawColor(SDLRenderer, 255, 0, 0, 255);
                        break;
                    case 4 :
                        SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 0, 255);
                        break;
                    case 11 :
                        SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 127, 255);
                        break;
                    case 12 :
                        SDL_SetRenderDrawColor(SDLRenderer, 127, 127, 127, 255);
                        break;
                    case 13 :
                        SDL_SetRenderDrawColor(SDLRenderer, 127, 0, 0, 255);
                        break;
                    case 14 :
                        SDL_SetRenderDrawColor(SDLRenderer, 127, 127, 0, 255);
                        break;
                    default: break;
                }
                //SDL_RenderFillRect(SDLRenderer, &newRect);
                drawingRectangle.h = 1;
                ty = 0;
                tyStep = 32/(float)newRect.h;
                for (int y = newRect.y; y<newRect.h+newRect.y; y++) {
                    color = firstTexture[(int)(ty)*32];
                    SDL_SetRenderDrawColor(SDLRenderer, color*255, color*255, color*255, 255);
                    drawingRectangle.y = y;
                    drawingRectangle.x = newRect.x;
                    SDL_RenderFillRect(SDLRenderer, &drawingRectangle);
                    ty += tyStep;
                }
                //SDL_RenderCopy(SDLRenderer, allTextureImage[0], NULL, &newRect);
            }
        }

        SDL_RenderPresent(SDLRenderer);

        SDL_Delay(20);
    }
    free(listOfRect);
    return EXIT_SUCCESS;
}
