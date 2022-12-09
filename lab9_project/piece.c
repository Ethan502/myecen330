#include "piece.h"

enum states { STOP, UP, DOWN, LEFT, RIGHT, DEAD };

void drawPiece(piece *p, uint16_t color) {
  display_fillRect(p->currX - 8, p->currY - 8, 16, 16, color);
}

void stop(piece *p) {
  p->ghostFlag = 2;
  p->currState = STOP;
}

void PieceInitPacman(piece *p) {
  p->currX = 160;
  p->currY = 120;
  p->type = PLAYER;
  p->currState = STOP;
  drawPiece(p, DISPLAY_YELLOW);
  p->color = DISPLAY_YELLOW;
}

void PieceInitInky(piece *p) {
  p->type = INKY;
  p->currState = LEFT;
  p->currX = 300;
  p->currY = 120;
  drawPiece(p, DISPLAY_CYAN);
  p->color = DISPLAY_CYAN;
  p->ghostFlag = 0;
}

void PieceInitClyde(piece *p) {
  p->type = CLYDE;
  p->currState = RIGHT;
  p->currX = 20;
  p->currY = 20;
  drawPiece(p, DISPLAY_GREEN);
  p->color = DISPLAY_GREEN;
  p->ghostFlag = 0;
}

void PieceInitBlinky(piece *p) {
  p->type = BLINKY;
  p->currState = DOWN;
  p->currX = 160;
  p->currY = 20;
  drawPiece(p, DISPLAY_RED);
  p->color = DISPLAY_RED;
  p->ghostFlag = 0;
}

void PieceInitPinky(piece *p) {
  p->type = PINKY;
  p->currState = LEFT;
  p->currX = 160;
  p->currY = 300;
  drawPiece(p, DISPLAY_MAGENTA);
  p->color = DISPLAY_MAGENTA;
  p->ghostFlag = 0;
}

void moveRight(piece *p) { p->currState = RIGHT; }
void moveLeft(piece *p) { p->currState = LEFT; }
void moveUp(piece *p) { p->currState = UP; }
void moveDown(piece *p) { p->currState = DOWN; };

void wallCheck(piece *p) {
  // the upper left block walls
  if ((p->currX > 30 && p->currX < 150) && // bottom wall
      (p->currY <= 112 && p->currY >= 90)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currY = 113;
    drawPiece(p, p->color);
  }
  if ((p->currX > 30 && p->currX < 150) && (p->currY <= 40 && p->currY >= 28)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currY = 27;
    drawPiece(p, p->color);
  }
  if ((p->currX > 28 && p->currX < 60) && (p->currY <= 112 && p->currY >= 30)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currX = 27;
    drawPiece(p, p->color);
  }
  if ((p->currX > 130 && p->currX < 152) &&
      (p->currY <= 112 && p->currY >= 30)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currX = 153;
    drawPiece(p, p->color);
  }

  // top right block
  if ((p->currX > 170 && p->currX < 290) &&
      (p->currY <= 112 && p->currY >= 90)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currY = 113;
    drawPiece(p, p->color);
  }
  if ((p->currX > 170 && p->currX < 290) &&
      (p->currY <= 40 && p->currY >= 28)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currY = 27;
    drawPiece(p, p->color);
  }
  if ((p->currX > 168 && p->currX < 180) &&
      (p->currY <= 112 && p->currY >= 30)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currX = 167;
    drawPiece(p, p->color);
  }
  if ((p->currX > 260 && p->currX < 292) &&
      (p->currY <= 112 && p->currY >= 30)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currX = 293;
    drawPiece(p, p->color);
  }

  // lower left block
  if ((p->currX > 30 && p->currX < 150) && // bottom wall
      (p->currY <= 212 && p->currY >= 190)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currY = 213;
    drawPiece(p, p->color);
  }
  if ((p->currX > 30 && p->currX < 150) &&
      (p->currY <= 140 && p->currY >= 128)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currY = 127;
    drawPiece(p, p->color);
  }
  if ((p->currX > 28 && p->currX < 60) &&
      (p->currY <= 212 && p->currY >= 130)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currX = 27;
    drawPiece(p, p->color);
  }
  if ((p->currX > 130 && p->currX < 152) &&
      (p->currY <= 212 && p->currY >= 130)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currX = 153;
    drawPiece(p, p->color);
  }

  // lower right block
  if ((p->currX > 170 && p->currX < 290) && // bottom wall
      (p->currY <= 212 && p->currY >= 190)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currY = 213;
    drawPiece(p, p->color);
  }
  if ((p->currX > 170 && p->currX < 290) &&
      (p->currY <= 140 && p->currY >= 128)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currY = 127;
    drawPiece(p, p->color);
  }
  if ((p->currX > 168 && p->currX < 180) &&
      (p->currY <= 212 && p->currY >= 130)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currX = 167;
    drawPiece(p, p->color);
  }
  if ((p->currX > 260 && p->currX < 292) &&
      (p->currY <= 212 && p->currY >= 130)) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currX = 293;
    drawPiece(p, p->color);
  }

  // four border walls
  if (p->currX - 8 <= 0) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currX = 9;
    drawPiece(p, p->color);
  }
  if (p->currX + 8 >= 320) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currX = 311;
    drawPiece(p, p->color);
  }
  if (p->currY - 8 <= 0) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currY = 9;
    drawPiece(p, p->color);
  }
  if (p->currY + 8 >= 240) {
    p->currState = STOP;
    drawPiece(p, DISPLAY_BLACK);
    p->currY = 231;
    drawPiece(p, p->color);
  }
}

void PieceTick(piece *p) {
  switch (p->currState) {
  case RIGHT:
    drawPiece(p, DISPLAY_BLACK);
    p->currX += CONFIG_PIECE_DISTANCE_PER_TICK;
    drawPiece(p, p->color);
    break;
  case LEFT:
    drawPiece(p, DISPLAY_BLACK);
    p->currX -= CONFIG_PIECE_DISTANCE_PER_TICK;
    drawPiece(p, p->color);
    break;
  case UP:
    drawPiece(p, DISPLAY_BLACK);
    p->currY -= CONFIG_PIECE_DISTANCE_PER_TICK;
    drawPiece(p, p->color);
    break;
  case DOWN:
    drawPiece(p, DISPLAY_BLACK);
    p->currY += CONFIG_PIECE_DISTANCE_PER_TICK;
    drawPiece(p, p->color);
    break;
  case STOP:
    if (p->type == INKY) {
      if (p->ghostFlag) {
        p->currState = LEFT;
        p->ghostFlag = 0;
      } else if (!p->ghostFlag) {
        p->currState = RIGHT;
        p->ghostFlag = 1;
      }
    }
    if (p->type == BLINKY) {
      if (p->ghostFlag) {
        p->currState = DOWN;
        p->ghostFlag = 0;
      } else if (!p->ghostFlag) {
        p->currState = UP;
        p->ghostFlag = 1;
      }
    }
    if (p->type == CLYDE) {
      if (p->ghostFlag) {
        p->currState = RIGHT;
        p->ghostFlag = 0;
      } else if (!p->ghostFlag) {
        p->currState = LEFT;
        p->ghostFlag = 1;
      }
    }
    if (p->type == PINKY) {
      if (p->ghostFlag) {
        p->currState = LEFT;
        p->ghostFlag = 0;
      } else if (!p->ghostFlag) {
        p->currState = RIGHT;
        p->ghostFlag = 1;
      }
    }
    break;
  }
}