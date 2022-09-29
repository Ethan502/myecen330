#include "interrupt_test.h"
#include "interrupts.h"
#include "intervalTimer.h"
#include "leds.h"

#define LED_0_MASK 0x01
#define LED_1_MASK 0x02
#define LED_2_MASK 0x04

#define TENHERTZ 0.1
#define ONEHERTZ 1
#define TENTHHERTZ 10

// function to blink the lights on the 0 timer
static void timer0_isr() {
  leds_write(leds_read() ^ LED_0_MASK);
  intervalTimer_ackInterrupt(INTERVAL_TIMER_0);
}

// function to blink the lights on the timer 1
static void timer1_isr() {
  leds_write(leds_read() ^ LED_1_MASK);
  intervalTimer_ackInterrupt(INTERVAL_TIMER_1);
}

// function to blink the lights on the timer 2
static void timer2_isr() {
  leds_write(leds_read() ^ LED_2_MASK);
  intervalTimer_ackInterrupt(INTERVAL_TIMER_2);
}

// this is the main function to test my interrupts and blink the lights
void interrupt_test_run() {
  leds_init();
  interrupts_init();

  // do stuff for the LED, blink at 10 Hz
  interrupts_register(INTERVAL_TIMER_0_INTERRUPT_IRQ, timer0_isr);
  interrupts_irq_enable(INTERVAL_TIMER_0_INTERRUPT_IRQ);

  intervalTimer_initCountDown(INTERVAL_TIMER_0, TENHERTZ);
  intervalTimer_enableInterrupt(INTERVAL_TIMER_0);
  intervalTimer_start(INTERVAL_TIMER_0);

  // do stuff for the LED 1, blink at 1 Hz
  interrupts_register(INTERVAL_TIMER_1_INTERRUPT_IRQ, timer1_isr);
  interrupts_irq_enable(INTERVAL_TIMER_1_INTERRUPT_IRQ);

  intervalTimer_initCountDown(INTERVAL_TIMER_1, ONEHERTZ);
  intervalTimer_enableInterrupt(INTERVAL_TIMER_1);
  intervalTimer_start(INTERVAL_TIMER_1);

  // do stuff for the LED 2, blink at .1 Hz
  interrupts_register(INTERVAL_TIMER_2_INTERRUPT_IRQ, timer2_isr);
  interrupts_irq_enable(INTERVAL_TIMER_2_INTERRUPT_IRQ);

  intervalTimer_initCountDown(INTERVAL_TIMER_2, TENTHHERTZ);
  intervalTimer_enableInterrupt(INTERVAL_TIMER_2);
  intervalTimer_start(INTERVAL_TIMER_2);

  while (1)
    ;
}