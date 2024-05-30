//
// Created by Mathi on 5/29/2024.
//

#include "SDLWindow.h"

void SDLDrawAndRefreshWindow(SDL_Renderer* renderer) {
    SDL_Point lotOfPoints[50];
    SDL_Rect rect = {100, 100, 100, 100};
    for (int i = 0; i<50; i++) {
        lotOfPoints[i].x = (i+1)*20;
        lotOfPoints[i].y = (i+1)*20;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderDrawPoints(renderer, lotOfPoints, 50);
    //SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void SDLQuit(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
}

SDL_Rect* createAllRect(int listOfBlock[10][10], int* logSize) {
    SDL_Rect* listOfRect = (SDL_Rect*) malloc(sizeof(SDL_Rect)*100);
    for (int i = 0; i< 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (listOfBlock[i][j] == 1) {
                listOfRect[*logSize].w = 192;
                listOfRect[*logSize].h = 108;
                listOfRect[*logSize].x = j*192;
                listOfRect[*logSize].y = i*108;
                *logSize += 1;
            }
        }
    }
    return listOfRect;
}