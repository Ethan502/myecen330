#ifndef PIECE_H
#define PIECE_H

#include "config.h"
#include "display.h"
#include "stdint.h"

typedef enum {
  PLAYER,
  INKY,
  PINKY,
  BLINKY,
  CLYDE,
} pieceType;

typedef struct {
  pieceType type; // what kind of piece is it

  int16_t currX; // the location of the piece
  int16_t currY;

  uint32_t currState; // current move state of the piece

  uint16_t color;

  int ghostFlag;

} piece;

void PieceInitPacman(piece *p);
void PieceInitInky(piece *p);
void PieceInitBlinky(piece *p);
void PieceInitClyde(piece *p);
void PieceInitPinky(piece *p);

void wallCheck(piece *p);

void drawPiece(piece *p, uint16_t color);

void moveRight(piece *p);
void moveLeft(piece *p);
void moveUp(piece *p);
void moveDown(piece *p);
void stop(piece *p);

void PieceTick(piece *p);
#endif