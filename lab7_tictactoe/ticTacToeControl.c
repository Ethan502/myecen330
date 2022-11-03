#include "ticTacToeControl.h"
#include "buttons.h"
#include "display.h"
#include "minimax.h"
#include "ticTacToe.h"
#include "ticTacToeDisplay.h"
#include "touchscreen.h"
#include <stdio.h>

#define MENU_WAIT_TIME 3
#define FIRSTDRAW_WAIT_TIME 4
#define ZERO 0
#define INSTRUCTIONS "TOUCH BOARD TO PLAY X OR WAIT FOR THE BOARD TO PLAY 0\n"
#define RESET_BUTTON 0x0001
#define NUM_SQUARES 9

#define MENU_ST_MSG "menu state\n"
#define FIRSTDRAW_MSG "in first draw\n"
#define COMPX_MSG "compX state\n"
#define COMPO_MSG "compO state\n"
#define USRX_MSG "usrX state\n"
#define USRO_MSG "usrO state\n"
#define END_MSG "end state\n"

static double ticks;
static bool cpu_isX;
static uint16_t wait_cnt;
static uint16_t menu_wait_ticks;
static uint16_t firstDraw_wait_ticks;
static bool firstTouch;
static tictactoe_board_t board;
static bool is_turn_over;
static tictactoe_location_t spot;
static tictactoe_location_t userSpot;
static bool firstX;

enum states { menu, firstDraw, compX, compO, usrX, usrO, end } currState;

// initialize the sm
void ticTacToeControl_init(double period_s) {
  menu_wait_ticks = MENU_WAIT_TIME / period_s;
  firstDraw_wait_ticks = FIRSTDRAW_WAIT_TIME / period_s;
  cpu_isX = false;
  firstTouch = false;
  wait_cnt = ZERO;
  is_turn_over = false;
  spot.row = 0;
  spot.column = 0;
  firstX = false;
  buttons_init();
  display_init();
  display_fillScreen(DISPLAY_DARK_BLUE);
  minimax_initBoard(&board);
  display_setTextColor(DISPLAY_WHITE);
  display_print(INSTRUCTIONS);
}

// manage all the sm ticks
void ticTacToeControl_tick() {

  switch (currState) {
  case menu: // the first menu state
    if (wait_cnt == menu_wait_ticks) {
      currState = firstDraw;
      display_setTextColor(DISPLAY_DARK_BLUE);
      display_print(INSTRUCTIONS);
      ticTacToeDisplay_init();
      wait_cnt = ZERO;
      break;
    } else if (wait_cnt != menu_wait_ticks) {
      currState = menu;
      break;
    }
  case firstDraw: // start state
    if ((wait_cnt == firstDraw_wait_ticks) &&
        (touchscreen_get_status() != TOUCHSCREEN_RELEASED)) {
      firstX = true;
      cpu_isX = true;
      currState = compX;
      break;
    } else if (touchscreen_get_status() == TOUCHSCREEN_RELEASED) {
      cpu_isX = false;
      currState = usrX;
      break;
    }
    // this section will handle if the computer is X------------------
  case compX:
    if (is_turn_over &&
        !minimax_isGameOver(minimax_computeBoardScore(&board, cpu_isX))) {
      currState = usrO;
      is_turn_over = false;
      break;
    } else if (minimax_isGameOver(minimax_computeBoardScore(&board, cpu_isX))) {
      currState = end;
      is_turn_over = false;
      break;
    }
  case usrO:
    if (is_turn_over &&
        !minimax_isGameOver(minimax_computeBoardScore(&board, cpu_isX))) {
      currState = compX;
      is_turn_over = false;
      break;
    } else if (minimax_isGameOver(minimax_computeBoardScore(&board, cpu_isX))) {
      currState = end;
      is_turn_over = false;
      break;
    }
    //-------------------------------------------------------------------
    // this section will handle if the user is X -------------------------
  case usrX: // if the user is this
    if (is_turn_over &&
        !minimax_isGameOver(minimax_computeBoardScore(&board, cpu_isX))) {
      currState = compO;
      touchscreen_ack_touch();
      is_turn_over = false;
      break;
    } else if (minimax_isGameOver(minimax_computeBoardScore(&board, cpu_isX))) {
      touchscreen_ack_touch();
      currState = end;
      is_turn_over = false;
      break;
    }

  case compO: // if the computer is O
    if (is_turn_over &&
        !minimax_isGameOver(minimax_computeBoardScore(&board, cpu_isX))) {
      touchscreen_ack_touch();
      currState = usrX;
      is_turn_over = false;
      break;
    } else if (minimax_isGameOver(minimax_computeBoardScore(&board, cpu_isX))) {
      touchscreen_ack_touch();
      currState = end;
      is_turn_over = false;
      break;
    }
    // -----------------------------------------------------------------------------
  case end:
    if (buttons_read() == RESET_BUTTON) {
      for (uint8_t i = 0; i < TICTACTOE_BOARD_ROWS; i++) {
        // loop through the columns
        for (uint8_t j = 0; j < TICTACTOE_BOARD_COLUMNS; j++) {
          if (board.squares[i][j] == MINIMAX_X_SQUARE) {
            spot.row = i;
            spot.column = j;
            ticTacToeDisplay_drawX(spot, true);
          }
          if (board.squares[i][j] == MINIMAX_O_SQUARE) {
            spot.row = i;
            spot.column = j;
            ticTacToeDisplay_drawO(spot, true);
          }
        }
      }
      currState = firstDraw;
      minimax_initBoard(&board);
      touchscreen_ack_touch();
      wait_cnt = 0;
      break;
    } else {
      // currState = end;
      break;
    }
  }

  switch (currState) { // all the moore outputs
  case menu:
    wait_cnt++;
    break;
  case firstDraw:
    wait_cnt++;
    break;
  case compX:
    userSpot = minimax_computeNextMove(&board, cpu_isX);
    ticTacToeDisplay_drawX(userSpot, false);
    board.squares[userSpot.row][userSpot.column] = MINIMAX_X_SQUARE;
    is_turn_over = true;
    break;
  case compO:
    userSpot = minimax_computeNextMove(&board, cpu_isX);
    ticTacToeDisplay_drawO(userSpot, false);
    board.squares[userSpot.row][userSpot.column] = MINIMAX_O_SQUARE;
    is_turn_over = true;
    break;
  case usrX:
    userSpot =
        ticTacToeDisplay_getLocationFromPoint(touchscreen_get_location());
    if (firstX) {
      userSpot.row = ZERO;
      userSpot.column = ZERO;
      ticTacToeDisplay_drawX(userSpot, false);
      board.squares[userSpot.row][userSpot.column] = MINIMAX_X_SQUARE;
      firstX = false;
      break;
    } else if (board.squares[userSpot.row][userSpot.column] ==
               MINIMAX_EMPTY_SQUARE) {
      ticTacToeDisplay_drawX(userSpot, false);
      board.squares[userSpot.row][userSpot.column] = MINIMAX_X_SQUARE;
      is_turn_over = true;
      touchscreen_ack_touch();
      break;
    } else {
      is_turn_over = false;
      touchscreen_ack_touch();
      break;
    }
  case usrO:
    userSpot =
        ticTacToeDisplay_getLocationFromPoint(touchscreen_get_location());
    if (board.squares[userSpot.row][userSpot.column] == MINIMAX_EMPTY_SQUARE) {
      ticTacToeDisplay_drawO(userSpot, false);
      board.squares[userSpot.row][userSpot.column] = MINIMAX_O_SQUARE;
      is_turn_over = true;
      touchscreen_ack_touch();
      break;
    } else {
      is_turn_over = false;
      touchscreen_ack_touch();
      break;
    }
  }
}

// if (minimax_isGameOver(score)) {
//   currState = end;
// } else if (!minimax_isGameOver(minimax_computeBoardScore(&board))) {
//   ticTacToeDisplay_drawX(minimax_computeNextMove(&board, cpu_isX), false);
// }