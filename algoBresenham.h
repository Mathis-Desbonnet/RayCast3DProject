//
// Created by Mathi on 5/30/2024.
//

#include <math.h>
#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 24
#define PI 3.14159

#ifndef RAYCAST3DPROJECT_ALGOBRESENHAM_H
#define RAYCAST3DPROJECT_ALGOBRESENHAM_H

void detectHigh(int x0, int y0, int x1, int y1, int** listOfBlock, SDL_Renderer* renderer, SDL_Point* point);
void detectLow(int x0, int y0, int x1, int y1, int** listOfBlock, SDL_Renderer* renderer, SDL_Point* point);
void detect(int x0, int y0, int x1, int y1, int** listOfBlock, int angle, SDL_Renderer* renderer, SDL_Point* point);
int DDA(float x0, float y0, int x1, int y1, int listOfBlock[SIZE][SIZE], int angle, SDL_Renderer* renderer, SDL_FPoint point[360], int typeOfWall[90], float ca[90], int texture[]);

double distance(int x0, int y0, double x1, double y1);

#endif //RAYCAST3DPROJECT_ALGOBRESENHAM_H
