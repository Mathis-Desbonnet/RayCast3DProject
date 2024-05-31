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

int** generateRect(int size) {
    int** rectList = (int**) malloc(sizeof(int*)*size);
    for (int i = 0; i<size; i++) {
        rectList[i] = (int*) malloc(sizeof(int)*size);
        for (int j = 0; j<size; j++) {
            if (rand()%10 > 8) {
                rectList[i][j] = 1;
            } else {
                rectList[i][j] = 0;
            }

        }
    }
    return rectList;
}

SDL_Rect* createAllRect(int listOfBlock[SIZE][SIZE], int* logSize) {
    SDL_Rect* listOfRect = (SDL_Rect*) malloc(sizeof(SDL_Rect)*SIZE*SIZE);
    for (int i = 0; i< SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (listOfBlock[i][j] > 0) {
                listOfRect[*logSize].w = 1920/SIZE;
                listOfRect[*logSize].h = 1080/SIZE;
                listOfRect[*logSize].x = j*(1920/SIZE);
                listOfRect[*logSize].y = i*(1080/SIZE);
                *logSize += 1;
            }
        }
    }
    return listOfRect;
}