#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "buttons.h"
#include "config.h"
#include "display.h"
#include "dots.h"
#include "math.h"
#include "piece.h"
#include "stdio.h"
#include "stdlib.h"

void gameControlInit(); // init variables and other stuff

void gameControlTick();

void drawBoard(); // draw the initial board

void checkCollision();

void initDots();
void drawDots();
void checkDotEat();

#endif