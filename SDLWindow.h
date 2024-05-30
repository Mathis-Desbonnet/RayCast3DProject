//
// Created by Mathi on 5/29/2024.
//

#include <SDL.h>

#ifndef RAYCAST3DPROJECT_SDLWINDOW_H
#define RAYCAST3DPROJECT_SDLWINDOW_H

void SDLDrawAndRefreshWindow(SDL_Renderer* renderer);
void SDLQuit(SDL_Window* window, SDL_Renderer* renderer);

SDL_Rect* createAllRect(int listOfBlock[10][10], int* logSize);

#endif //RAYCAST3DPROJECT_SDLWINDOW_H
