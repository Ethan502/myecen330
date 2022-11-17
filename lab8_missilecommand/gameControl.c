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
#define ZERO 0
#define ONE 1
#define QUARTER_WIDTH DISPLAY_WIDTH / 4
#define SCORE_Y 5
#define SCORE_WRITE_OFFSET 40

#define ONE_THIRD_WIDTH DISPLAY_WIDTH / 3
#define TWO_THIRD_WIDTH ONE_THIRD_WIDTH * 2

#define IMPACTED_WRITE_OFFSET 55
#define THREE_QUARTERS_WIDTH (QUARTER_WIDTH * 3)
#define SCORE_LOCATION_ADJUST 30

// start up the arrays for good and bad missiles
missile_t all_missiles[CONFIG_MAX_TOTAL_MISSILES];
missile_t *bad_missiles = &(all_missiles[0]);
missile_t *good_missiles = &(all_missiles[CONFIG_MAX_ENEMY_MISSILES + ONE]);
missile_t *plane_missile = &(all_missiles[CONFIG_MAX_ENEMY_MISSILES]);
static bool first_half = true;
static int playerShots;
static int oldShots;
static int oldImpacts;
static int newImpacts;

void addImpact() { // function to update and rewrite the impacts counter
  display_setCursor(TWO_THIRD_WIDTH - SCORE_LOCATION_ADJUST, SCORE_Y);
  display_setTextColor(DISPLAY_BLACK);
  display_println("Impacted: ");
  display_setCursor(
      TWO_THIRD_WIDTH - SCORE_LOCATION_ADJUST + IMPACTED_WRITE_OFFSET, SCORE_Y);
  display_printDecimalInt(oldImpacts);

  oldImpacts = newImpacts;

  display_setCursor(TWO_THIRD_WIDTH - SCORE_LOCATION_ADJUST, SCORE_Y);
  display_setTextColor(DISPLAY_WHITE);
  display_println("Impacted: ");
  display_setCursor(
      TWO_THIRD_WIDTH - SCORE_LOCATION_ADJUST + IMPACTED_WRITE_OFFSET, SCORE_Y);
  display_printDecimalInt(newImpacts);
}

void updateShot() { // function to update and rewrite the shots counter
  display_setCursor(ONE_THIRD_WIDTH - SCORE_LOCATION_ADJUST, SCORE_Y);
  display_setTextColor(DISPLAY_BLACK);
  display_println("Shots: ");
  display_setCursor(
      ONE_THIRD_WIDTH - SCORE_LOCATION_ADJUST + SCORE_WRITE_OFFSET, SCORE_Y);
  display_printDecimalInt(oldShots);

  oldShots = playerShots;

  display_setCursor(ONE_THIRD_WIDTH - SCORE_LOCATION_ADJUST, SCORE_Y);
  display_setTextColor(DISPLAY_WHITE);
  display_println("Shots: ");
  display_setCursor(
      ONE_THIRD_WIDTH - SCORE_LOCATION_ADJUST + SCORE_WRITE_OFFSET, SCORE_Y);
  display_printDecimalInt(playerShots);
}

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

  plane_init(plane_missile); // init the plane and its missile
  //  put the stats in here too

  playerShots = 0;
  oldShots = 0;
  newImpacts = -1;
  oldImpacts = -1;
  updateShot();
}

// function to tick the game control
void gameControl_tick() {

  // check to see if the enemey missiles have impacted
  for (int i = 0; i < CONFIG_MAX_ENEMY_MISSILES + ONE; i++) {
    if (all_missiles[i].impacted) {
      newImpacts++;
      all_missiles[i].impacted = false;
    }
  }

  bool launched_player = false; // make sure two missiles wont launch

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
        playerShots++;
        launched_player = true;
      }
    }
    launched_player = false;
    touchscreen_ack_touch(); // acknowledge the touch
  }
  // tick only first half the missiles per cycle
  if (first_half) {
    addImpact();
    for (uint16_t i = 0; i < HALF_MISSILES; i++) {
      missile_tick(&all_missiles[i]);
    }
    first_half = !first_half;
  } else if (!first_half) { // tick the second half of the missiles and the
                            // score counter and the plane
    updateShot();
    plane_tick();
    for (uint16_t i = HALF_MISSILES; i < CONFIG_MAX_TOTAL_MISSILES; i++) {
      missile_tick(&all_missiles[i]);
    }
    first_half = !first_half;
  }

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
      display_point_t planeSpot = plane_getXY();
      // math to see if missiles are in explosion radii
      int16_t delta_y = bad_missiles[i].y_current - all_missiles[j].y_current;
      int16_t delta_x = bad_missiles[i].x_current - all_missiles[j].x_current;
      int16_t planeDeltaX = planeSpot.x - all_missiles[j].x_current;
      int16_t planeDeltaY = planeSpot.y - all_missiles[j].y_current;
      if (((delta_y * delta_y) + (delta_x * delta_x)) <
          (all_missiles[j].radius * all_missiles[j].radius)) {
        missile_trigger_explosion(&bad_missiles[i]);
      }
      if (((planeDeltaY * planeDeltaY) + (planeDeltaX * planeDeltaX)) <
          (all_missiles[j].radius * all_missiles[j].radius)) {
        plane_explode();
      }
    }
  }
}