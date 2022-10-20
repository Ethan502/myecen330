#include "clockControl.h"
#include "clockDisplay.h"
#include "display.h"
#include "stdio.h"
#include "touchscreen.h"

#define DELAY_SECONDS_TO_WAIT 0.5
#define FAST_SECONDS_TO_WAIT 0.1
#define NONE 0;

#define WAIT_ST_MSG "wait state\n"
#define INC_DEC_MSG "IncDec\n"
#define FAST_UPDATE_MSG "fast state\n"
#define LONG_DELAY_MSG "long delay state\n"

enum states { WAITING, INC_DEC, LONG_PRESS_DELAY, FAST_UPDATE } currState;

static int timer;
static double delay_num_ticks;
static int delay_cnt;
static int update_cnt;
static double update_num_ticks;

void debugStatePrint() {

  static enum states previousState;
  static bool firstPass = true;
  // Only print the message if:
  // 1. This the first pass and the value for previousState is unknown.
  // 2. previousState != currentState - this prevents reprinting the same state
  // name over and over.
  if (previousState != currState || firstPass) {
    firstPass = false; // previousState will be defined, firstPass is false.
    previousState = currState; // keep track of the last

    // switch statement to update the states and mealy outputs

    switch (currState) {
    case WAITING:
      printf(WAIT_ST_MSG);
      break;
    case INC_DEC:
      printf(INC_DEC_MSG);
      break;
    case FAST_UPDATE:
      printf(FAST_UPDATE_MSG);
      break;
    case LONG_PRESS_DELAY:
      printf(LONG_DELAY_MSG);
      break;
    default:
      printf("odd\n");
    }
  }
}

void clockControl_init(double period_s) {
  timer = NONE;
  delay_cnt = NONE;
  update_cnt = NONE;
  delay_num_ticks = DELAY_SECONDS_TO_WAIT / period_s;
  update_num_ticks = FAST_SECONDS_TO_WAIT / period_s;
  currState = WAITING;
}

void clockControl_tick() {
  debugStatePrint();

  // switch statement to control the transition and mealy parts of the SM
  switch (currState) {
  case WAITING: // items in the waiting state
    if (touchscreen_get_status() == TOUCHSCREEN_PRESSED) {
      delay_cnt = NONE;
      currState = LONG_PRESS_DELAY;
      break;
    } else // loop through if nothing happened
    {
      currState = WAITING;
      break;
    }
  case LONG_PRESS_DELAY: // items if the screen is pressed longer than half a
                         // second
    if (touchscreen_get_status() == TOUCHSCREEN_RELEASED) {
      currState = INC_DEC;
      break;
    } else if (delay_cnt ==
               delay_num_ticks) // if the clock has ticked half a second
    {
      update_cnt = NONE;
      currState = FAST_UPDATE;
      break;
    } else // stay in the same state if nothing changes
    {
      currState = LONG_PRESS_DELAY;
      break;
    }
  case INC_DEC: // basic increment state
    if (touchscreen_get_status() == TOUCHSCREEN_RELEASED) {
      touchscreen_ack_touch();
      currState = WAITING;
      break;
    }
  case FAST_UPDATE: // state to update the state super fast
    if ((touchscreen_get_status() != TOUCHSCREEN_RELEASED) &&
        (update_cnt == update_num_ticks)) // the the screen is released and it
                                          // has ticked for a tenth of a second
    {
      update_cnt = 0;
      clockDisplay_performIncDec(touchscreen_get_location());
      currState = FAST_UPDATE;
      break;
    } else if (touchscreen_get_status() ==
               TOUCHSCREEN_RELEASED) // check if touchscreen is released
    {
      touchscreen_ack_touch();
      currState = WAITING;
      break;
    } else {
      currState = FAST_UPDATE;
      break;
    }
  }

  // switch statement for the Moore cases of the SM
  switch (currState) {
  case WAITING:
    break;
  case INC_DEC:
    clockDisplay_performIncDec(
        touchscreen_get_location()); // increment or decrease it
    break;
  case LONG_PRESS_DELAY:
    delay_cnt++; // count the delay state
    break;
  case FAST_UPDATE:
    update_cnt++; // count the fast update
    break;
  }
}
