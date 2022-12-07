#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "config.h"
#include "display.h"

void gameControlInit(); // init variables and other stuff

void drawBoard(); // draw the initial board

void drawPiece(display_point_t spot);

#endif