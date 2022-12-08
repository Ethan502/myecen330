#include "piece.h"

enum states { STOP, UP, DOWN, LEFT, RIGHT, DEAD };

void drawPiece(piece *p, uint16_t color) {
  display_fillRect(p->currX - 8, p->currY - 8, 16, 16, color);
}

PieceInitPacman(piece *p) {
  p->currX = 160;
  p->currY = 120;
  p->type = PLAYER;
  p->currState = STOP;
  drawPiece(p, DISPLAY_YELLOW);
}

void moveRight(piece *p) { p->currState = RIGHT; }

void PieceTick(piece *p) {
  switch (p->currState) {
  case RIGHT:
    drawPiece(p, DISPLAY_BLACK);
    p->currX += CONFIG_PIECE_DISTANCE_PER_TICK;
    drawPiece(p, DISPLAY_YELLOW);
    break;
  case STOP:
    break;
  }
}