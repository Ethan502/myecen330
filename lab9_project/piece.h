#ifndef PIECE_H
#define PIECE_H

#include "config.h"
#include "display.h"
#include "stdint.h"

typedef enum {
  PLAYER,
  ENEMY,
} pieceType;

typedef struct {
  pieceType type; // what kind of piece is it

  uint16_t currX; // the location of the piece
  uint16_t currY;

  uint32_t currState; // current move state of the piece

} piece;

void PieceInitPacman(piece *p);

void drawPiece(piece *p, uint16_t color);

void moveRight(piece *p);

void PieceTick(piece *p);
#endif