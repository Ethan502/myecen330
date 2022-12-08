#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "buttons.h"
#include "config.h"
#include "display.h"
#include "piece.h"
#include "walls.h"

void gameControlInit(); // init variables and other stuff

void gameControlTick();

void drawBoard(); // draw the initial board

#endif