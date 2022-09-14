
#ifndef GPIOTEST
#define GPIOTEST

#include "switches.h"
#include "buttons.h"
#include "leds.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "display.h"

#define ZEROS 0x0000
#define ONES 0x0F

#define WIDTH_THREEFOURTHS (DISPLAY_WIDTH/4)*3
#define WIDTH_HALF DISPLAY_WIDTH/2
#define WIDTH_FOURTH DISPLAY_WIDTH/4

#define BTN0_TEXT_WIDTH ((DISPLAY_WIDTH/4)*3)+20
#define BTN1_TEXT_WIDTH (DISPLAY_WIDTH/2) + 20
#define BTN2_TEXT_WIDTH (DISPLAY_WIDTH/4) + 20
#define BTN3_TEXT_WIDTH 20
#define TEXT_SIZE 2

#define HEIGHT_HALF DISPLAY_HEIGHT/2
#define HEIGHT_FIFTH DISPLAY_HEIGHT/5

#define Y_UPPER_BOUND 0

// Runs a test of the buttons. As you push the buttons, graphics and messages
// will be written to the LCD panel. The test will until all 4 pushbuttons are
// simultaneously pressed.
void gpioTest_buttons();

// Runs a test of the switches. As you slide the switches, LEDs directly above
// the switches will illuminate. The test will run until all switches are slid
// upwards. When all 4 slide switches are slid upward, this function will
// return.
void gpioTest_switches();

#endif /* GPIOTEST */
