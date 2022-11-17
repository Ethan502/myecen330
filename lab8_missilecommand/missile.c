#include "missile.h"
#include "config.h"
#include "display.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

#define FIRST_SIXTH_HEIGHT (DISPLAY_HEIGHT / 6)
#define SQUARED 2
#define ZERO 0

#define ONE_THIRD_WIDTH (DISPLAY_WIDTH / 3)
#define TWO_THIRD_WIDTH (ONE_THIRD_WIDTH * 2)

#define ONE_QUARTER_WIDTH (DISPLAY_WIDTH / 4)
#define ONE_HALF_WIDTH (ONE_QUARTER_WIDTH * 2)
#define THREE_QUARTERS_WIDTH (ONE_QUARTER_WIDTH * 3)

#define IMPACTED_WRITE_OFFSET 70

#define SCORE_Y 5

#define OFFSET_FOR_STATS 6

static int oldImpacts = 0;
static int newImpacts = 0;

enum states { INIT, MOVE, EXGROW, EXSHRINK, DEAD };

// init function to make the missile dead
void missile_init_dead(missile_t *missile) { missile->currentState = DEAD; }

// does the init stuff for the plane that is for all the planes
static void general_init(missile_t *missile) {
  // math to find the total length
  int16_t y_comp = missile->y_dest - missile->y_origin;
  int16_t x_comp = missile->x_dest - missile->x_origin;
  missile->total_length = sqrt((pow(y_comp, SQUARED)) + (pow(x_comp, SQUARED)));
  // printf("length: %d\n", missile->total_length);
  // set the radius
  missile->radius = 0;
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
  missile->y_origin = rand() % FIRST_SIXTH_HEIGHT + OFFSET_FOR_STATS;
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
  missile->y_origin = DISPLAY_HEIGHT;

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
  missile->x_dest = rand() % DISPLAY_WIDTH;
  missile->y_dest = DISPLAY_HEIGHT;

  general_init(missile);

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

void missile_trigger_explosion(missile_t *missile) {
  missile->explode_me = true;
}

// do the repeated updates of the missile paths
static void update_current(missile_t *missile) {
  double percentage;
  percentage = missile->length / missile->total_length;
  missile->x_current =
      missile->x_origin + percentage * (missile->x_dest - missile->x_origin);
  missile->y_current =
      missile->y_origin + percentage * (missile->y_dest - missile->y_origin);
}

void missile_tick(missile_t *missile) {
  // all the mealy outputs
  switch (missile->currentState) {
  case MOVE: // if the missile is moving to the desination
    if (missile->explode_me) {
      display_drawLine(missile->x_origin, missile->y_origin, missile->x_current,
                       missile->y_current, DISPLAY_BLACK);
      missile->currentState = EXGROW;
      break;
    } else if (missile->length >= missile->total_length) {
      if (missile->type == MISSILE_TYPE_ENEMY) {
        missile->impacted = true;     // impact the missile
        missile->currentState = DEAD; // reset the red enemy missiles
        display_drawLine(missile->x_origin, missile->y_origin,
                         missile->x_current, missile->y_current, DISPLAY_BLACK);
      } else if (missile->type == MISSILE_TYPE_PLAYER) {
        display_drawLine(missile->x_origin, missile->y_origin,
                         missile->x_current, missile->y_current, DISPLAY_BLACK);
        missile->currentState = EXGROW; // make the green missiles explode
      } else if (missile->type == MISSILE_TYPE_PLANE) {
        missile->currentState = DEAD;
        missile->impacted = true; // impact the missile
        display_drawLine(missile->x_origin, missile->y_origin,
                         missile->x_current, missile->y_current, DISPLAY_BLACK);
      }
    }
    break;

  case EXGROW: // this will need to change for the next lab, add red missile
               // explosions
    if (missile->radius >= CONFIG_EXPLOSION_MAX_RADIUS) {
      missile->currentState = EXSHRINK;
      break;
    }

  case EXSHRINK: // make the explosions shrink
    if (missile->radius <= ZERO) {
      display_fillCircle(missile->x_current, missile->y_current,
                         missile->radius, DISPLAY_BLACK);
      missile->currentState = DEAD;
      break;
    }
  }
  // all the moore outputs
  switch (missile->currentState) {
  case MOVE:
    display_drawLine(missile->x_origin, missile->y_origin, missile->x_current,
                     missile->y_current, DISPLAY_BLACK);
    if (missile->type == MISSILE_TYPE_ENEMY) {
      missile->length += CONFIG_ENEMY_MISSILE_DISTANCE_PER_TICK * 2;
      if (missile->length > missile->total_length) {
        missile->length = missile->total_length;
      }
      update_current(missile); // do the normal line updates with the percentage
      display_drawLine(missile->x_origin, missile->y_origin, missile->x_current,
                       missile->y_current, DISPLAY_RED);
      break;
    } else if (missile->type == MISSILE_TYPE_PLAYER) {
      missile->length += CONFIG_PLAYER_MISSILE_DISTANCE_PER_TICK * 2;
      if (missile->length > missile->total_length) {
        missile->length = missile->total_length;
      }
      update_current(missile); // do the normal line updates with the percentage
      display_drawLine(missile->x_origin, missile->y_origin, missile->x_current,
                       missile->y_current, DISPLAY_GREEN);
      break;
    } else if (missile->type == MISSILE_TYPE_PLANE) {
      missile->length += CONFIG_ENEMY_MISSILE_DISTANCE_PER_TICK * 2;
      if (missile->length > missile->total_length) {
        missile->length = missile->total_length;
      }
      update_current(missile);
      display_drawLine(missile->x_origin, missile->y_origin, missile->x_current,
                       missile->y_current, DISPLAY_WHITE);
      break;
    }
  // increase the explosion radius in this state
  case EXGROW:
    if (missile->type == MISSILE_TYPE_PLAYER) {
      missile->radius += CONFIG_EXPLOSION_RADIUS_CHANGE_PER_TICK * 2;
      display_fillCircle(missile->x_current, missile->y_current,
                         missile->radius, DISPLAY_GREEN);
    } else if (missile->type == MISSILE_TYPE_ENEMY) {
      missile->radius += CONFIG_EXPLOSION_RADIUS_CHANGE_PER_TICK * 2;
      display_fillCircle(missile->x_current, missile->y_current,
                         missile->radius, DISPLAY_RED);
    } else if (missile->type == MISSILE_TYPE_PLANE) {
      missile->radius += CONFIG_EXPLOSION_RADIUS_CHANGE_PER_TICK * 2;
      display_fillCircle(missile->x_current, missile->y_current,
                         missile->radius, DISPLAY_WHITE);
    }
    break;
  case EXSHRINK: // make the explosions shrink
    display_fillCircle(missile->x_current, missile->y_current, missile->radius,
                       DISPLAY_BLACK);

    missile->radius -= CONFIG_EXPLOSION_RADIUS_CHANGE_PER_TICK * 2;
    if (missile->type == MISSILE_TYPE_PLAYER) {
      display_fillCircle(missile->x_current, missile->y_current,
                         missile->radius, DISPLAY_GREEN);
    } else if (missile->type == MISSILE_TYPE_ENEMY) {
      display_fillCircle(missile->x_current, missile->y_current,
                         missile->radius, DISPLAY_RED);
    } else if (missile->type == MISSILE_TYPE_PLANE) {
      display_fillCircle(missile->x_current, missile->y_current,
                         missile->radius, DISPLAY_WHITE);
    }
    break;
  }
}