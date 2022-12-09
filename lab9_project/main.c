#include "stdio.h"

#include "buttons.h"
#include "display.h"
#include "interrupts.h"
#include "intervalTimer.h"

#include "config.h"
#include "gameControl.h"

volatile bool interrupt_flag;

uint32_t isr_triggered_count;
uint32_t isr_handled_count;

void game_isr() {
  gameControlTick();
  intervalTimer_ackInterrupt(INTERVAL_TIMER_0);
}

int main() {

  display_init();
  buttons_init();
  gameControlInit();
  // init for the game stuff

  // here is all the interrupt things i dont really understand
  interrupts_init();
  interrupts_irq_enable(INTERVAL_TIMER_0_INTERRUPT_IRQ);
  interrupts_register(INTERVAL_TIMER_0_INTERRUPT_IRQ, game_isr);
  intervalTimer_initCountDown(INTERVAL_TIMER_0, CONFIG_GAME_TIMER_PERIOD);
  intervalTimer_enableInterrupt(INTERVAL_TIMER_0);

  intervalTimer_start(INTERVAL_TIMER_0);

  while (1) {
  }
}