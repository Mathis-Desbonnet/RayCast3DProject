//
// Created by Mathi on 5/29/2024.
//

#include "Player.h"

Player* createPlayer(int posX, int posY, int size, int FOV) {
    Player* newPlayer = (Player*) malloc(sizeof(Player));
    newPlayer->posX = posX;
    newPlayer->posY = posY;
    newPlayer->size = size;
    newPlayer->FOV = FOV;
    return newPlayer;
}

void showPlayer(Player* player, SDL_Renderer* renderer) {
    SDL_RenderDrawPoint(renderer, player->posX, player->posY);
}

void movePlayer(Player *firstPlayer, int speed, const Uint8 *keyState, SDL_Rect *playerRect, SDL_FPoint* viewPoint, float angle) {
    if (keyState[SDL_GetScancodeFromKey(SDLK_z)] || keyState[SDL_GetScancodeFromKey(SDLK_UP)]) {
        firstPlayer->posY += speed*sin(angle);
        firstPlayer->posX += speed*cos(angle);
        (*playerRect).y += speed*sin(angle);
        (*playerRect).x += speed*cos(angle);
        viewPoint->y += speed*sin(angle);
        viewPoint->x += speed*cos(angle);
    }
    if (keyState[SDL_GetScancodeFromKey(SDLK_s)] || keyState[SDL_GetScancodeFromKey(SDLK_DOWN)]) {
        firstPlayer->posY -= speed*sin(angle);
        firstPlayer->posX -= speed*cos(angle);
        (*playerRect).y -= speed*sin(angle);
        (*playerRect).x -= speed*cos(angle);
        viewPoint->y -= speed*sin(angle);
        viewPoint->x -= speed*cos(angle);
    }
    if (keyState[SDL_GetScancodeFromKey(SDLK_q)] || keyState[SDL_GetScancodeFromKey(SDLK_RIGHT)]) {
        firstPlayer->posY += speed*cos(angle);
        firstPlayer->posX += speed*sin(angle);
        (*playerRect).y += speed*cos(angle);
        (*playerRect).x += speed*sin(angle);
        viewPoint->y += speed*cos(angle);
        viewPoint->x += speed*sin(angle);
    }
    if (keyState[SDL_GetScancodeFromKey(SDLK_d)] || keyState[SDL_GetScancodeFromKey(SDLK_LEFT)]) {
        firstPlayer->posY -= speed*cos(angle);
        firstPlayer->posX -= speed*sin(angle);
        (*playerRect).y -= speed*cos(angle);
        (*playerRect).x -= speed*sin(angle);
        viewPoint->y -= speed*cos(angle);
        viewPoint->x -= speed*sin(angle);
    }
}

void calculateAnglePointPlayer(const Player *firstPlayer, int angle, float x, float y, float xPlayerPosView,
                               float yPlayerPosView, SDL_FPoint *viewPointWall, SDL_FPoint *viewPointPlayer) {
    (*viewPointWall).x = (cosf((angle * PI / 180)) * x) - (sinf(angle * PI / 180) * y);
    (*viewPointWall).y = (cosf(angle * PI / 180) * y) + (sinf(angle * PI / 180) * x);
    (*viewPointPlayer).x = firstPlayer->posX+25+((cosf((angle*PI/180))*xPlayerPosView) - (sinf(angle*PI/180)*yPlayerPosView));
    (*viewPointPlayer).y = firstPlayer->posY+25+((cosf(angle*PI/180)*yPlayerPosView) + (sinf(angle*PI/180)*xPlayerPosView));
}

void changeAngle(int* angle, const Uint8* keyState) {
    if (keyState[SDL_GetScancodeFromKey(SDLK_a)]) {
        (*angle)--;
    } else if (keyState[SDL_GetScancodeFromKey(SDLK_e)]) {
        (*angle)++;
    }
}