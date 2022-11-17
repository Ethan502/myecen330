#include "gameControl.h"
#include "config.h"
#include "display.h"
#include "intervalTimer.h"
#include "math.h"
#include "missile.h"
#include "plane.h"
#include "stdio.h"
#include "stdlib.h"
#include "touchscreen.h"

#define HALF_MISSILES CONFIG_MAX_TOTAL_MISSILES / 2
#define SQUARE 2
#define ONE 1

// start up the arrays for good and bad missiles
missile_t all_missiles[CONFIG_MAX_TOTAL_MISSILES];
missile_t *bad_missiles = &(all_missiles[0]);
missile_t *good_missiles = &(all_missiles[CONFIG_MAX_ENEMY_MISSILES + ONE]);
missile_t *plane_missile = &(all_missiles[CONFIG_MAX_ENEMY_MISSILES]);
static bool first_half = true;

// initialize all the game control stuff
void gameControl_init() {
  display_fillScreen(DISPLAY_BLACK);
  // initialize all the enemy missiles as dead
  for (uint16_t i = 0; i < CONFIG_MAX_ENEMY_MISSILES; i++) {
    missile_init_dead(&bad_missiles[i]);
  }
  for (uint16_t i = 0; i < CONFIG_MAX_PLAYER_MISSILES; i++) {
    missile_init_dead(&good_missiles[i]);
  }

  plane_init(plane_missile);
  // put the stats in here too
}

// function to tick the game control
void gameControl_tick() {

  bool launched_player = false;

  // reinitialize enemy missiles
  for (uint16_t i = 0; i < CONFIG_MAX_ENEMY_MISSILES; i++) {
    if (missile_is_dead(&bad_missiles[i])) {
      missile_init_enemy(&bad_missiles[i]);
    }
  }
  // launch player missiles if the screen has been touched, if there are
  // available missiles
  if (touchscreen_get_status() == TOUCHSCREEN_RELEASED) {
    for (uint16_t i = 0; i < CONFIG_MAX_PLAYER_MISSILES; i++) {
      if (missile_is_dead(&good_missiles[i]) && !launched_player) {
        display_point_t spot = touchscreen_get_location();
        missile_init_player(&good_missiles[i], spot.x, spot.y);
        launched_player = true;
      }
    }
    launched_player = false;
    touchscreen_ack_touch(); // acknowledge the touch
  }
  // tick only first half the missiles per cycle
  if (first_half) {
    for (uint16_t i = 0; i < HALF_MISSILES; i++) {
      missile_tick(&all_missiles[i]);
    }
    first_half = !first_half;
  } else if (!first_half) { // tick the second half of the missiles
    for (uint16_t i = HALF_MISSILES; i < CONFIG_MAX_TOTAL_MISSILES; i++) {
      missile_tick(&all_missiles[i]);
    }
    first_half = !first_half;
  }

  plane_tick();

  // check to see if any collisions are happening
  for (uint16_t i = 0; i < CONFIG_MAX_ENEMY_MISSILES + ONE; i++) {
    for (uint16_t j = 0; j < CONFIG_MAX_TOTAL_MISSILES; j++) {
      if (!missile_is_flying(
              &bad_missiles[i])) { // ignore if the missles isnt flying
        continue;
      }
      if (!missile_is_exploding(
              &all_missiles[j])) { // ignore if missile isnt exploding
        continue;
      }
      // math to see if missiles are in explosion radii
      int16_t delta_y = bad_missiles[i].y_current - all_missiles[j].y_current;
      int16_t delta_x = bad_missiles[i].x_current - all_missiles[j].x_current;
      if (((delta_y * delta_y) + (delta_x * delta_x)) <
          (all_missiles[j].radius * all_missiles[j].radius)) {
        missile_trigger_explosion(&bad_missiles[i]);
      }
    }
  }
}