#include "display.h"
#include "math.h"
#include "missile.h"
#include "stdio.h"
#include "stdlib.h"

#define FIRST_SIXTH_HEIGHT = DISPLAY_HEIGHT / 6
#define SQUARED 2

#define ONE_THIRD_WIDTH = DISPLAY_WIDTH / 3
#define TWO_THIRD_WIDTH = ONE_THIRD_WIDTH * 2

#define ONE_QUARTER_WIDTH = DISPLAY_WIDTH / 4
#define ONE_HALF_WIDTH = ONE_QUARTER_WIDTH * 2
#define THREE_QUARTERS_WIDTH = ONE_QUARTER_WIDTH * 3

enum states { INIT, MOVE, EXGROW, EXSHRINK, DEAD } currState;

// init function to make the missile dead
void missile_init_dead(missile_t *missile) { missile->currentState = DEAD; }

void general_init(missile_t *missile) {
  // math to find the total length
  uint16_t y_comp = missile->y_dest - missile->y_origin;
  uint16_t x_comp = missile->x_dest - missile->x_origin;
  missile->total_length = sqrt(pow(y_comp, SQUARED) + pow(x_comp, SQUARED));
  // reset the length
  missile->length = 0;
  // reset the current to the origin
  missile->x_current = missile->x_origin;
  missile->y_current = missile->y_origin;
  // change the impact to false
  missile->impacted = false;
  // change explode me to false
  missile->explode_me = false;
}

// initialize for an enemy missle
void missile_init_enemy(missile_t *missile) {
  missile->type = MISSILE_TYPE_ENEMY;
  // set the origin randomly in the top of the screen
  missile->x_origin = rand() % DISPLAY_WIDTH;
  missile->y_origin = rand() % FIRST_SIXTH_HEIGHT;
  // set the destination point randomly, but along the bottom edge
  missile->x_dest = rand() % DISPLAY_WIDTH;
  missile->y_dest = DISPLAY_HEIGHT;
  // call the general initializations
  general_init(missile);
  // set the current state
  missile->currentState = MOVE;
}

// initialize the player missile
void missile_init_player(missile_t *missile, uint16_t x_dest, uint16_t y_dest) {
  missile->type = MISSILE_TYPE_PLAYER;
  // determine which launch station the missile should shoot from
  if (x_dest <= ONE_THIRD_WIDTH) {
    missile->x_origin = ONE_QUARTER_WIDTH;
  } else if (x_dest < TWO_THIRD_WIDTH) {
    missile->x_origin = ONE_HALF_WIDTH;
  } else {
    missile->x_origin = THREE_QUARTERS_WIDTH;
  }
  missile->y_origin = rand() % DISPLAY_HEIGHT;

  // set the destination as provided
  missile->x_dest = x_dest;
  missile->y_dest = y_dest;

  // call the general initializations
  general_init(missile);
  // set the current state
  missile->currentState = MOVE;
}

void missile_init_plane(missile_t *missile, int16_t plane_x, int16_t plane_y) {
  missile->type = MISSILE_TYPE_PLANE;
  // set the origin
  missile->x_origin = plane_x;
  missile->y_origin = plane_y;
  // set the destination
  missile->x_dest = rand() % DISPALY_WIDTH;
  missile->y_dest = DISPLAY_HEIGHT;

  // set the current state
  missile->currentState = MOVE;
}
// see if the missile is in the dead state
bool missile_is_dead(missile_t *missile) {
  if (missile->currentState == DEAD) {
    return true;
  } else {
    return false;
  }
}
// see if the missile is exploding
bool missile_is_exploding(missile_t *missile) {
  if (missile->currentState == EXGROW || missile->currentState == EXSHRINK) {
    return true;
  } else {
    return false;
  }
}
// see if the missile is flying/moving
bool missile_is_flying(missile_t *missile) {
  if (missile->currentState == MOVE) {
    return true;
  } else {
    return false;
  }
}

void missile_trigger_explosion(missile_t *missile) {}

void missile_tick(missile_t *missile) {}