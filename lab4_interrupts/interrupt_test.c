#include "leds.h"
#include "interrupts.h"
#include "intervalTimer.h"
#include "interrupt_test.h"

bool on = false;

static void myIsr()
{
if(on)
{
   leds_write(0x0000);
   on = false;
}
else if(!on)
{
    leds_write(0x0001);
    on = true;
}
intervalTimer_ackInterrupt(INTERVAL_TIMER_0);
}

// void interrupt_test_run() 
// {
// interrupts_init();
// interrupts_register(INTERVAL_TIMER_0_INTERRUPT_IRQ, myIsr);
// interrupts_irq_enable(INTERVAL_TIMER_0_INTERRUPT_IRQ);
// intervalTimer_initCountDown(INTERVAL_TIMER_0, 1);
// intervalTimer_enableInterrupt(INTERVAL_TIMER_0);
// intervalTimer_start(INTERVAL_TIMER_0);
// while (1);
// }


void interrupt_test_run()
{
    leds_init();
    interrupts_init();

    interrupts_register(INTERVAL_TIMER_0_INTERRUPT_IRQ,myIsr);
    interrupts_irq_enable(INTERVAL_TIMER_0_INTERRUPT_IRQ);

    intervalTimer_initCountDown(INTERVAL_TIMER_0,1);
    intervalTimer_enableInterrupt(INTERVAL_TIMER_0);
    intervalTimer_start(INTERVAL_TIMER_0);

    while(1);
}