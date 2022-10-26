#include "ticTacToeControl.h"
#include "ticTacToeDisplay.h"
#include <stdio.h>
#include "display.h"

#define STATE_MACHINE_TIME 1
#define ZERO 0
#define INSTRUCTIONS "TOUCH BOARD TO PLAY X OR WAIT FOR THE BOARD TO PLAY 0\n"

static double ticks;
static bool cpu_isX;
static uint8_t wait_cnt;

void ticTacToeControl_init(double period_s)
{
    display_init();
    display_fillScreen(DISPLAY_BLACK);
    ticks = STATE_MACHINE_TIME / period_s;
    cpu_isX = false;
    wait_cnt = 0;
    display_setTextColor(DISPLAY_WHITE);
    display_println(INSTRUCTIONS);
}

void ticTacToeControl_tick()
{

}

