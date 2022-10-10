#include "touchscreen.h"
#include "display.h"
#include "stdio.h"

#define SECONDS_TO_WAIT 0.05

#define WAIT_ST_MSG "wait state\n"
#define NEVER_TOUCHED_ST_MSG "default\n"
#define BEING_TOUCHED_ST_MSG "being touched, waiting the 50ms\n"
#define PRESSED_ST_MSG "pressed state\n"

enum states { WAITING, ADC_SETTLING, PRESSED_ST } CURR_STATE;

static int adc_timer;
static double adc_settle_ticks;
static touchscreen_status_t touchStatus;
static bool isAckd = false;
static display_point_t point;

// the state debugger

// initialize the touchscreen SM variables and initial state
void touchscreen_init(double period_seconds) {
  adc_timer = 0;
  adc_settle_ticks = SECONDS_TO_WAIT / period_seconds;
  isAckd = true;
  CURR_STATE = WAITING;
}

// track my ticks and the state machine
void touchscreen_tick() {
  // print the debug statement
  

  // switch statement to update the states and mealy outputs
  uint8_t z;
  switch (CURR_STATE) {
  case WAITING:
    if (display_isTouched()) {
      display_clearOldTouchData();
      CURR_STATE = ADC_SETTLING;
    }
    break;

  case ADC_SETTLING:
    if (!display_isTouched()) {
      CURR_STATE = WAITING;
    } else if (display_isTouched && (adc_timer == adc_settle_ticks)) {
      display_getTouchedPoint(&point.x, &point.y, &z);
      CURR_STATE = PRESSED_ST;
    }
    break;

  case PRESSED_ST:
    touchStatus = TOUCHSCREEN_PRESSED;
    if (!display_isTouched()) {
      touchStatus = TOUCHSCREEN_RELEASED;
      CURR_STATE = WAITING;
    }
    break;
  default:
    printf(NEVER_TOUCHED_ST_MSG);
  }

  // switch statement to update the variables/moore outputs
  switch (CURR_STATE) {
  case WAITING:
    adc_timer = 0;
    if (isAckd) {
      touchStatus = TOUCHSCREEN_IDLE;
    }
    break;

  case ADC_SETTLING:
    adc_timer++;
    break;

  case PRESSED_ST:
    isAckd = false;
    break;
  default:
    printf(NEVER_TOUCHED_ST_MSG);
  }
}

// return the status of the touchscreen
touchscreen_status_t touchscreen_get_status() { return touchStatus; }

// acknowledge if the screen was touched correctly
void touchscreen_ack_touch() {
  if (touchStatus == TOUCHSCREEN_RELEASED) {
    isAckd = true;
  }
}

// return the touch point as a display point data type
display_point_t touchscreen_get_location() { return point; }
