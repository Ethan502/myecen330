#include "gpioTest.h"
#include "buttons.h"
#include "display.h"
#include "leds.h"
#include "switches.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define ZEROS 0x0000
#define ONES 0x0F

#define WIDTH_THREEFOURTHS (DISPLAY_WIDTH / 4) * 3
#define WIDTH_HALF DISPLAY_WIDTH / 2
#define WIDTH_FOURTH DISPLAY_WIDTH / 4
#define RECT_WIDTH 80

#define BTN0_TEXT_WIDTH ((DISPLAY_WIDTH / 4) * 3) + 20
#define BTN1_TEXT_WIDTH (DISPLAY_WIDTH / 2) + 20
#define BTN2_TEXT_WIDTH (DISPLAY_WIDTH / 4) + 20
#define BTN3_TEXT_WIDTH 20
#define TEXT_SIZE 2

#define HEIGHT_HALF DISPLAY_HEIGHT / 2
#define HEIGHT_FIFTH DISPLAY_HEIGHT / 5

#define Y_UPPER_BOUND 0
#define X_LEFT_BOUND 0

// test the switches
void gpioTest_switches() {
  switches_init();
  leds_init();
  bool sw0Check = false;
  bool sw1Check = false;
  bool sw2Check = false;
  bool sw3Check = false;

  // loop to constantly update the values
  while (1) {
    // read the switch values
    uint8_t val = switches_read();
    uint8_t curr = 0x00;

    // check to see if all the switches are on
    if ((val & ONES) == ONES) {
      break;
    }
    // write the value to the LEDs
    leds_write(val);
  }
  // turn LEDs off when the program ends
  leds_write(ZEROS);
}

// test the buttons
void gpioTest_buttons() {
  bool btn0Push = false;
  bool btn1Push = false;
  bool btn2Push = false;
  bool btn3Push = false;

  buttons_init();
  display_init();
  display_fillScreen(DISPLAY_BLACK);

  // loop to constantly perform the button logic
  while (1) {
    uint8_t val = buttons_read();

    if (val == ONES) {
      display_fillScreen(DISPLAY_BLACK);
      break;
    }

    // check and see if the button 0 is pressed
    if (((BUTTONS_BTN0_MASK & val) == BUTTONS_BTN0_MASK) && !btn0Push) {
      display_fillRect(WIDTH_THREEFOURTHS, Y_UPPER_BOUND, RECT_WIDTH,
                       HEIGHT_HALF, DISPLAY_YELLOW);

      display_setTextColor(DISPLAY_WHITE);
      display_setTextSize(TEXT_SIZE);
      display_setCursor(BTN0_TEXT_WIDTH, HEIGHT_FIFTH);
      display_println("BTN0");

      btn0Push = true;
    }
    // if not pressed, turn off the button block
    else if ((BUTTONS_BTN0_MASK & val) != BUTTONS_BTN0_MASK) {
      display_fillRect(WIDTH_THREEFOURTHS, Y_UPPER_BOUND, RECT_WIDTH,
                       HEIGHT_HALF, DISPLAY_BLACK);
      btn0Push = false;
    }

    // check and see if the button 1 is pressed
    if (((BUTTONS_BTN1_MASK & val) == BUTTONS_BTN1_MASK) && !btn1Push) {
      display_fillRect(WIDTH_HALF, Y_UPPER_BOUND, RECT_WIDTH, HEIGHT_HALF,
                       DISPLAY_RED);

      display_setTextColor(DISPLAY_WHITE);
      display_setTextSize(TEXT_SIZE);
      display_setCursor(BTN1_TEXT_WIDTH, HEIGHT_FIFTH);
      display_println("BTN1");

      btn1Push = true;
    }
    // if not pressed, turn off the button block
    else if ((BUTTONS_BTN1_MASK & val) != BUTTONS_BTN1_MASK) {
      display_fillRect(WIDTH_HALF, Y_UPPER_BOUND, RECT_WIDTH, HEIGHT_HALF,
                       DISPLAY_BLACK);
      btn1Push = false;
    }

    // check to see if the button 2 is pressed
    if (((BUTTONS_BTN2_MASK & val) == BUTTONS_BTN2_MASK) && !btn2Push) {
      display_fillRect(WIDTH_FOURTH, Y_UPPER_BOUND, RECT_WIDTH, HEIGHT_HALF,
                       DISPLAY_BLUE);

      display_setTextColor(DISPLAY_WHITE);
      display_setTextSize(TEXT_SIZE);
      display_setCursor(BTN2_TEXT_WIDTH, HEIGHT_FIFTH);
      display_println("BTN2");

      btn2Push = true;
    }
    // if not pressed, turn off the button block
    else if ((BUTTONS_BTN2_MASK & val) != BUTTONS_BTN2_MASK) {
      display_fillRect(WIDTH_FOURTH, Y_UPPER_BOUND, RECT_WIDTH, HEIGHT_HALF,
                       DISPLAY_BLACK);
      btn2Push = false;
    }

    // check to see if the button 3 is pressed
    if (((BUTTONS_BTN3_MASK & val) == BUTTONS_BTN3_MASK) && !btn3Push) {
      display_fillRect(X_LEFT_BOUND, Y_UPPER_BOUND, RECT_WIDTH, HEIGHT_HALF,
                       DISPLAY_GREEN);

      display_setTextColor(DISPLAY_WHITE);
      display_setTextSize(TEXT_SIZE);
      display_setCursor(BTN3_TEXT_WIDTH, HEIGHT_FIFTH);
      display_println("BTN3");

      btn3Push = true;
    }
    // if not pressed, turn off the button block
    else if ((BUTTONS_BTN3_MASK & val) != BUTTONS_BTN3_MASK) {
      display_fillRect(X_LEFT_BOUND, Y_UPPER_BOUND, RECT_WIDTH, HEIGHT_HALF,
                       DISPLAY_BLACK);
      btn3Push = false;
    }
  }
}