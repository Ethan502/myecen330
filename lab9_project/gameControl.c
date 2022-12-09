#include "gameControl.h"

piece all_pieces[CONFIG_MAX_PIECES_ALLOWED];
piece *pacman = &(all_pieces[0]);
piece *ghosts = &(all_pieces[1]);

bool btn0Push = false;
bool btn1Push = false;
bool btn2Push = false;
bool btn3Push = false;

int dotsEaten = 0;

dot dot1;
dot dot2;
dot dot3;
dot dot4;
dot dot5;
dot dot6;
dot dot7;
dot dot8;
dot dot9;

dot *dots[9] = {&dot1, &dot2, &dot3, &dot4, &dot5, &dot6, &dot7, &dot8, &dot9};

void winGame() {
  for (int i = 0; i < CONFIG_MAX_PIECES_ALLOWED; i++) {
    stop(&(all_pieces[i]));
  }
  display_fillScreen(DISPLAY_GREEN);
  display_setCursor(80, 120);
  display_setTextColor(DISPLAY_WHITE);
  display_setTextSize(2);
  display_println("YOU WIN!!");
}

void menu() {
  display_fillScreen(DISPLAY_BLUE);
  display_setCursor(50, 80);
  display_setTextColor(DISPLAY_YELLOW);
  display_setTextSize(5);
  display_println("POOKMAN");
  display_setCursor(90, 130);
  display_setTextColor(DISPLAY_WHITE);
  display_setTextSize(2);
  display_println("BTN3: LEFT");
  display_setCursor(90, 150);
  display_println("BTN2: UP");
  display_setCursor(90, 170);
  display_println("BTN1: DOWN");
  display_setCursor(90, 190);
  display_println("BTN0: RIGHT");

  display_setCursor(50, 220);
  display_println("Press Btn0 to begin");

  while (1) {
    uint8_t val = buttons_read();
    if ((val & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK && !btn0Push) {
      break;
    }
  }
}

void initDots() {
  dot1.x = 20;
  dot1.y = 20;
  dot1.eaten = false;

  dot2.x = 160;
  dot2.y = 20;
  dot2.eaten = false;

  dot3.x = 300;
  dot3.y = 20;
  dot3.eaten = false;

  dot4.x = 20;
  dot4.y = 120;
  dot4.eaten = false;

  dot5.x = 160;
  dot5.y = 120;
  dot5.eaten = false;

  dot6.x = 300;
  dot6.y = 120;
  dot6.eaten = false;

  dot7.x = 20;
  dot7.y = 220;
  dot7.eaten = false;

  dot8.x = 160;
  dot8.y = 220;
  dot8.eaten = false;

  dot9.x = 300;
  dot9.y = 220;
  dot9.eaten = false;
}

void drawDots() {
  for (int i = 0; i < 9; i++) {
    if (!dots[i]->eaten)
      display_fillCircle(dots[i]->x, dots[i]->y, 3, DISPLAY_WHITE);
  }
}

void drawRects() {
  // make the top two rectangles
  display_fillRect(40, 40, 100, 60, DISPLAY_BLUE);
  display_fillRect(180, 40, 100, 60, DISPLAY_BLUE);

  // make the bottom two rectangles
  display_fillRect(40, 140, 100, 60, DISPLAY_BLUE);
  display_fillRect(180, 140, 100, 60, DISPLAY_BLUE);
}

void drawBoard() {
  display_fillScreen(DISPLAY_BLACK);
  drawRects();
}

int distanceDot(dot *p) {
  return sqrt(((pacman->currX - p->x) * (pacman->currX - p->x)) +
              ((pacman->currY - p->y) * (pacman->currY - p->y)));
}

void checkDotEat() {
  for (int i = 0; i < 9; i++) {
    if (!dots[i]->eaten) {
      if (distanceDot((dots[i])) <= 8) {
        dots[i]->eaten = true;
        dotsEaten++;
      }
    }
  }
  if (dotsEaten == 9) {
    winGame();
  }
}

void gameControlInit() {
  menu();
  drawBoard();
  initDots();
  drawDots();
  PieceInitPacman(pacman);
  PieceInitBlinky(&(ghosts[0]));
  PieceInitInky(&(ghosts[1]));
  PieceInitClyde(&(ghosts[2]));
  PieceInitPinky(&(ghosts[3]));
}

void endgame() {
  for (int i = 0; i < CONFIG_MAX_PIECES_ALLOWED; i++) {
    stop(&(all_pieces[i]));
  }
  display_fillScreen(DISPLAY_BLACK);
  display_setCursor(80, 120);
  display_setTextColor(DISPLAY_WHITE);
  display_setTextSize(2);
  display_println("YOU LOSE!! :,(");
  display_setCursor(120, 150);
  display_setTextColor(DISPLAY_WHITE);
  display_setTextSize(1);
  display_println("go cry about it");
  exit(0);
}

int distance(piece *p) {
  return sqrt(((pacman->currX - p->currX) * (pacman->currX - p->currX)) +
              ((pacman->currY - p->currY) * (pacman->currY - p->currY)));
}

void checkCollision() {
  for (int i = 0; i < 3; i++) {
    if (distance(&(ghosts[i])) < 8) {
      endgame();
    }
  }
}

void gameControlTick() {
  uint8_t val = buttons_read();
  if ((val & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK && !btn0Push) {
    moveRight(pacman);
    // drawRects();
  }
  if ((val & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK && !btn3Push) {
    moveLeft(pacman);
    // drawRects();
  }
  if ((val & BUTTONS_BTN2_MASK) == BUTTONS_BTN2_MASK && !btn2Push) {
    moveUp(pacman);
    // drawRects();
  }
  if ((val & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK && !btn1Push) {
    moveDown(pacman);
    // drawRects();
  }

  // printf("i get here\n");
  for (int i = 0; i < CONFIG_MAX_PIECES_ALLOWED; i++) {
    PieceTick(&(all_pieces[i]));
    wallCheck(&(all_pieces[i]));
  }

  for (int i = 0; i < 4; i++) {
    checkCollision(&(ghosts[i]));
  }
  drawDots();
  checkDotEat();
}
