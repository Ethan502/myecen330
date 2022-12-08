#ifndef WALLS_H
#define WALLS_H

#include "display.h"
#include "piece.h"

typedef struct{
    display_point_t start;
    display_point_t end;

    //void checkCollision(piece p);
}wall;

#endif