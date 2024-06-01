//
// Created by Mathi on 5/30/2024.
//

#include "algoBresenham.h"

void detectHigh(int x0, int y0, int x1, int y1, int** listOfBlock, SDL_Renderer* renderer, SDL_Point* point) {
    int deltaX, deltaY, D, xi, x;

    deltaX = x1 - x0;
    deltaY = y1 - y0;
    xi = 1;


    if (deltaX < 0) {
        xi = -1;
        deltaX = -deltaX;
    }

    D = 2*deltaX-deltaY;

    point->x = x0*(1920/SIZE);
    point->y = y0*(1080/SIZE);
    x = x0;


    for (int y = y0; y<y1; y++) {

        point->x = x*(1920/SIZE);
        point->y = y*(1080/SIZE);

        if (y >= SIZE || y < 0 || x >= SIZE || x < 0) {
            point->x = x0*(1920/SIZE);
            point->y = y0*(1080/SIZE);
            return;
        }
        if (listOfBlock[y][x] == 1) {
            return;
        }
        if (D > 0) {
            x += xi;
            D += 2*(deltaX-deltaY);
        } else {
            D += 2*deltaX;
        }
    }
}
void detectLow(int x0, int y0, int x1, int y1, int** listOfBlock, SDL_Renderer* renderer, SDL_Point* point) {
    int deltaX, deltaY, D, yi, y;

    deltaX = x1 - x0;
    deltaY = y1 - y0;
    yi = 1;

    if (deltaY < 0) {
        yi = -1;
        deltaY = -deltaY;
    }

    D = (2*deltaY)-deltaX;

    point->x = x0*(1920/SIZE);
    point->y = y0*(1080/SIZE);
    y = y0;

    for (int x = x0; x<x1; x++) {
        point->x = x*(1920/SIZE);
        point->y = y*(1080/SIZE);
        if (x >= SIZE || x < 0 || y >= SIZE || y < 0) {
            point->x = x0*(1920/SIZE);
            point->y = y0*(1080/SIZE);
            return;
        }
        if (listOfBlock[y][x] == 1) {
            return;
        }
        if (D > 0) {
            y += yi;
            D += 2*(deltaY-deltaX);
        } else {
            D += 2*deltaY;
        }
    }
}
void detect(int x0, int y0, int x1, int y1, int** listOfBlock, int angle, SDL_Renderer* renderer, SDL_Point* point) {
    if (abs(y1 - y0) < abs(x1 - x0)) {
        if (x0 > x1) {
            detectLow(x1, y1, x0, y0, listOfBlock, renderer, point);
        } else {
            detectLow(x0, y0, x1, y1, listOfBlock, renderer, point);
        }
    } else {

        if (y0 > y1) {
            detectHigh(x1, y1, x0, y0, listOfBlock, renderer, point);
        } else {
            detectHigh(x0, y0, x1, y1, listOfBlock, renderer, point);
        }
    }
}

double distance(float x0, float y0, float x1, float y1) {
    return sqrtf(((x1-x0)*(x1-x0))+((y1-y0)*(y1-y0)));
}

void DDA(float x0, float y0, int x1, int y1, int listOfBlock[SIZE][SIZE], int angle, SDL_Renderer* renderer, SDL_Point* point) {
    int mx, my, mp, stop, ra;
    float rx1, ry1, rx2, ry2, xo, yo, aTan, nTan;
    ra = angle%360;
    while (ra < 0) {
        ra += 360;
    }
    for (int r = 0; r<1; r++) {
        stop = 0;
        aTan = -(1/tanf(ra*PI/180));
        if (ra > 180) {
            ry1 = y0;
            rx1 = (y0-ry1)*aTan+x0;
            yo = -5;
            xo = -yo*aTan;
        } if (ra < 180) {
            ry1 = y0 + 5;
            rx1 = (y0-ry1)*aTan+x0;
            yo = 5;
            xo = -yo*aTan;
        } if (ra == 0) {
            rx1 = 10000;
            ry1 = y0;
            stop = SIZE*SIZE;
        }
        if (ra == 180) {
            rx1 = -10000;
            ry1 = y0;
            stop = SIZE*SIZE;
        }
        while (stop < SIZE*SIZE) {

            mx = (int) (rx1)/(1920/SIZE);
            my = (int) (ry1)/(1080/SIZE);
            //SDL_Log("%f %f %d\t %f %f\t %d %d", rx, ry, ra, x0, y0, mx, my);
            mp = my*SIZE+mx;
            if (mx >= 0 && mx < SIZE && my >= 0 && my < SIZE && listOfBlock[my][mx] > 0) {
                stop = SIZE*SIZE;
            } else {
                rx1 += xo;
                ry1 += yo;
                stop++;
            }

        }
        stop = 0;
        nTan = -tan(ra*PI/180);
        if (ra > 90 && ra < 270) {
            rx2 = x0;
            ry2 = (x0-rx2)*nTan+y0;
            xo = -5;
            yo = -xo*nTan;
        } if (ra < 90 || ra > 270) {
            rx2 = x0 + 5;
            ry2 = (x0-rx2)*nTan+y0;
            xo = 5;
            yo = -xo*nTan;
        } if (ra == 270) {
            rx2 = x0;
            ry2 = -2000;
            stop = SIZE*SIZE;
        }
        if (ra == 90) {
            rx2 = x0;
            ry2 = 2000;
            stop = SIZE*SIZE;
        }
        while (stop < SIZE*SIZE) {

            mx = (int) (rx2)/(1920/SIZE);
            my = (int) (ry2)/(1080/SIZE);
            //SDL_Log("%f %f %d\t %f %f\t %d %d\t %d", rx2, ry2, ra, x0, y0, mx, my, angle);
            mp = my*SIZE+mx;
            if (mx >= 0 && mx < SIZE && my >= 0 && my < SIZE && listOfBlock[my][mx] > 0) {
                stop = SIZE*SIZE;
            } else {
                rx2 += xo;
                ry2 += yo;
                stop++;
            }

        }
        //SDL_Log("");
        //SDL_Log("");
        //SDL_Log("");
//        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
//        SDL_RenderDrawLineF(renderer, x0, y0, rx1, ry1);
//        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//        SDL_RenderDrawLineF(renderer, x0, y0, rx2, ry2);
        point->x = 10000;
        point->y = 10000;
        if (distance(x0, y0, rx1, ry1) >= distance(x0, y0, rx2, ry2) && !(ra == 90 || ra == 270)) {
            if (((rx2 < 1920 && rx2 > 0) || (ry2 < 1080 && ry2 < 0))) {
                point->x = rx2;
                point->y = ry2;
            }
            //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            //SDL_RenderDrawLineF(renderer, x0, y0, rx2, ry2);
        } else if (distance(x0, y0, rx1, ry1) >= 10){
            if (((rx1 < 1920 && rx1 > 0) || (ry1 < 1080 && ry1 < 0)) && distance(x0, y0, rx1, ry1) > 10) {
                point->x = rx1;
                point->y = ry1;
            }
            //SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
            //SDL_RenderDrawLineF(renderer, x0, y0, rx1, ry1);
        }
    }
}