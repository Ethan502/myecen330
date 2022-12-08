#include "gameControl.h"

piece all_pieces[CONFIG_MAX_PIECES_ALLOWED];
piece *pacman = &(all_pieces[0]);
piece *ghosts = &(all_pieces[1]);

bool btn0Push = false;
bool btn1Push = false;
bool btn2Push = false;
bool btn3Push = false;

void drawBoard() {
  display_fillScreen(DISPLAY_BLACK);

  // make the top two rectangles
  display_fillRect(40, 40, 100, 60, DISPLAY_BLUE);
  display_fillRect(180, 40, 100, 60, DISPLAY_BLUE);

  // make the bottom two rectangles
  display_fillRect(40, 140, 100, 60, DISPLAY_BLUE);
  display_fillRect(180, 140, 100, 60, DISPLAY_BLUE);

  // make the pacman just for testing purposes
}

void gameControlInit() {
  drawBoard();
  buttons_init();
  PieceInitPacman(pacman);
}

void gameControlTick() {
  uint8_t val = buttons_read();
  if ((val & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK && !btn0Push) {
    moveRight(pacman);
  }

  pieceTick();
}
