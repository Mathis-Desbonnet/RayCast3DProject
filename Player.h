//
// Created by Mathi on 5/29/2024.
//

#include <stdlib.h>
#include <SDL.h>
#include <math.h>
#define PI 3.14159265

#ifndef RAYCAST3DPROJECT_PLAYER_H
#define RAYCAST3DPROJECT_PLAYER_H

typedef struct {
    int posX;
    int posY;
    int size;
    int FOV;
} Player;

Player* createPlayer(int posX, int posY, int size, int FOV);
void showPlayer(Player* player, SDL_Renderer* renderer);
void movePlayer(Player* player, int speed, const Uint8* keyState, SDL_Rect* playerRect, SDL_FPoint* viewPoint, float angle);
void calculateAnglePointPlayer(const Player *firstPlayer, float angle, float x, float y, float xPlayerPosView,
                               float yPlayerPosView, SDL_FPoint *viewPointWall, SDL_FPoint *viewPointPlayer);
void changeAngle(float* angle, const Uint8* keyState);

#endif //RAYCAST3DPROJECT_PLAYER_H
