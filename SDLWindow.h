//
// Created by Mathi on 5/29/2024.
//

#include <SDL.h>
#define SIZE 24

#ifndef RAYCAST3DPROJECT_SDLWINDOW_H
#define RAYCAST3DPROJECT_SDLWINDOW_H

void SDLDrawAndRefreshWindow(SDL_Renderer* renderer);
void SDLQuit(SDL_Window* window, SDL_Renderer* renderer);

int** generateRect(int size);
SDL_Rect* createAllRect(int listOfBlock[SIZE][SIZE], int* logSize);

#endif //RAYCAST3DPROJECT_SDLWINDOW_H
