/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.

Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.

For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

#include <stdio.h>

#include "display.h"

#define TEXT_SIZE 2
#define CURSOR_X0 0
#define CURSOR_Y0 0
#define CURSOR_X1 DISPLAY_WIDTH
#define CURSOR_Y1 DISPLAY_HEIGHT

#define TOP_TRIANGLE_BOTTOMX (DISPLAY_WIDTH / 2)
#define TOP_TRIANGLE_BOTTOMY (DISPLAY_HEIGHT / 2 - 20)
#define TOP_TRIANGLE_LEFTX (DISPLAY_WIDTH / 3 + 20)
#define TOP_TRIANGLE_BASEY (DISPLAY_HEIGHT / 6)
#define TOP_TRIANGLE_RIGHTX ((DISPLAY_WIDTH / 3) * 2 - 20)

#define BOTTOM_TRIANGLE_TOPX (DISPLAY_WIDTH / 2)
#define BOTTOM_TRIANGLE_TOPY (DISPLAY_HEIGHT / 2 + 20)
#define BOTTOM_TRIANGLE_LEFTX (DISPLAY_WIDTH / 3 + 20)
#define BOTTOM_TRIANGLE_BASEY ((DISPLAY_HEIGHT / 6) * 5)
#define BOTTOM_TRIANGLE_RIGHTX ((DISPLAY_WIDTH / 3) * 2 - 20)

#define LEFT_CIRCLE_CENTERX DISPLAY_WIDTH / 4
#define LEFT_CIRCLE_CENTERY DISPLAY_HEIGHT / 2

#define RIGHT_CIRCLE_CENTERX (DISPLAY_WIDTH / 4) * 3
#define RIGHT_CIRCLE_CENTERY DISPLAY_HEIGHT / 2

#define CIRCLE_RADIUS 30

// Print out "hello world" on both the console and the LCD screen.
int main() {

  // Initialize display driver, and fill screen with black
  display_init();
  display_fillScreen(DISPLAY_BLACK); // Blank the screen.

  // Draw the two green cross lines
  display_setTextColor(DISPLAY_GREEN); // Make the text red.
  display_drawLine(CURSOR_X0, CURSOR_Y0, CURSOR_X1, CURSOR_Y1, DISPLAY_GREEN);
  display_drawLine(CURSOR_X1, CURSOR_Y0, CURSOR_X0, CURSOR_Y1, DISPLAY_GREEN);

  // draw the top triangle
  display_drawTriangle(TOP_TRIANGLE_BOTTOMX, TOP_TRIANGLE_BOTTOMY,
                       TOP_TRIANGLE_LEFTX, TOP_TRIANGLE_BASEY,
                       TOP_TRIANGLE_RIGHTX, TOP_TRIANGLE_BASEY, DISPLAY_YELLOW);
  // draw the filled bottom triangle
  display_fillTriangle(BOTTOM_TRIANGLE_TOPX, BOTTOM_TRIANGLE_TOPY,
                       BOTTOM_TRIANGLE_LEFTX, BOTTOM_TRIANGLE_BASEY,
                       BOTTOM_TRIANGLE_RIGHTX, BOTTOM_TRIANGLE_BASEY,
                       DISPLAY_YELLOW);

  // draw the left circle
  display_drawCircle(LEFT_CIRCLE_CENTERX, LEFT_CIRCLE_CENTERY, CIRCLE_RADIUS,
                     DISPLAY_RED);

  // draw the right filled circle
  display_fillCircle(RIGHT_CIRCLE_CENTERX, RIGHT_CIRCLE_CENTERY, CIRCLE_RADIUS,
                     DISPLAY_RED);

  // Also print out 'line' on the terminal (stdout).
  printf("line\n");
  return 0;
}
