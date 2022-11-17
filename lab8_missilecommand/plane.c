#include "plane.h"
#include "config.h"
#include "display.h"
#include "math.h"
#include "missile.h"
#include "stdio.h"

#define PLANE_HEIGHT DISPLAY_HEIGHT / 3
#define PLANE_X_OFFSET 10
#define PLANE_Y_OFFSET 5
#define PLANE_SECONDS_TO_WAIT 6
#define ZERO 0

enum states { MOVE, DEAD } currState;

static display_point_t planeCenter;
static bool killPlane = false;
static uint16_t planeWait;
static uint16_t waitCount;
static bool shotMissile;
display_point_t shootLocation;
missile_t *pMissile;

void plane_explode() { killPlane = true; }

// helper function to draw the plane
void draw_plane(uint16_t x, uint16_t color) {
  display_fillTriangle(x + PLANE_X_OFFSET, PLANE_HEIGHT + PLANE_Y_OFFSET,
                       x + PLANE_X_OFFSET, PLANE_HEIGHT - PLANE_Y_OFFSET,
                       x - PLANE_X_OFFSET, PLANE_HEIGHT, color);
}

void plane_init(missile_t *plane_missile) {
  // set the state
  currState = MOVE;

  // make a more local pointer to the missile
  pMissile = plane_missile;

  // set some plane stuff
  planeCenter.x = DISPLAY_WIDTH;
  planeCenter.y = PLANE_HEIGHT;
  pMissile->currentState = DEAD;

  // counters and checkers
  planeWait = PLANE_SECONDS_TO_WAIT / CONFIG_GAME_TIMER_PERIOD;
  waitCount = ZERO;
  shotMissile = false;
  shootLocation.x = rand() % DISPLAY_WIDTH;
}

void plane_tick() {
  switch (currState) { // switch statement for the mealy
  case MOVE:           // if the plane is moving
    if (killPlane) {
      currState = DEAD;
      draw_plane(planeCenter.x, DISPLAY_BLACK);
      planeCenter.x = DISPLAY_WIDTH;
      waitCount = ZERO;
    } else if (planeCenter.x <= ZERO) {
      draw_plane(planeCenter.x, DISPLAY_BLACK);
      currState = DEAD;
      waitCount = ZERO;
      planeCenter.x = DISPLAY_WIDTH;
    }
    break;
  case DEAD: // if the plane is dead
    if (waitCount >= planeWait) {
      currState = MOVE;
      shootLocation.x = rand() % DISPLAY_WIDTH;
      draw_plane(planeCenter.x, DISPLAY_WHITE);
    }
    shotMissile = false;
    break;
  }

  switch (currState) { // switch statement for the moore stuff
  case MOVE:
    draw_plane(planeCenter.x, DISPLAY_BLACK);
    planeCenter.x -= CONFIG_PLANE_DISTANCE_PER_TICK;
    draw_plane(planeCenter.x, DISPLAY_WHITE);
    if (!shotMissile && (planeCenter.x <= shootLocation.x)) {
      missile_init_plane(pMissile, planeCenter.x, planeCenter.y);
      shotMissile = true;
    }
    break;
  case DEAD:
    waitCount++;
    break;
  }
}

// return the plane's location
display_point_t plane_getXY() { return planeCenter; }
