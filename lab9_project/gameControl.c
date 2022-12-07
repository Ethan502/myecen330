#include "gameControl.h"

void drawBoard() { display_fillScreen(DISPLAY_BLACK); }

void gameControlInit() { drawBoard(); }

void drawPiece(display_point_t spot) {
  display_fillRect(spot.x, spot.y, 15, 15, DISPLAY_YELLOW);
}