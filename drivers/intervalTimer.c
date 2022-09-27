#include "xil_io.h"
#include "xparameters.h"
#include <stdio.h>

#define TCSR0 0x0000
#define TLR0 0x0004
#define TCR0 0x0008

#define TCSR1 0x10
#define TLR1 0x14
#define TCR1 0x18

#define ZERO 0
#define HEX_ONE 0x0001
#define BIT_SHIFT_FOR_SECONDS 32

#define CASC_BIT 11
#define UDT0_BIT 1
#define LOAD0_BIT 5
#define ENT0_BIT 7
#define ARHT_BIT 4
#define ENIT_BIT 6
#define TINT_BIT 8

// function to write to any of the registers
static void writeRegister(uint32_t num, uint32_t offset, uint32_t value) {
  if (num == XPAR_AXI_TIMER_0_DEVICE_ID) {
    Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + offset, value);
  } else if (num == XPAR_AXI_TIMER_1_DEVICE_ID) {
    Xil_Out32(XPAR_AXI_TIMER_1_BASEADDR + offset, value);
  } else if (num == XPAR_AXI_TIMER_2_DEVICE_ID) {
    Xil_Out32(XPAR_AXI_TIMER_2_BASEADDR + offset, value);
  }
}

// read the values at the register of the inputed timer id number
static uint32_t readRegister(uint32_t num, uint32_t offset) {
  if (num == XPAR_AXI_TIMER_0_DEVICE_ID) {
    return Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + offset);
  } else if (num == XPAR_AXI_TIMER_1_DEVICE_ID) {
    return Xil_In32(XPAR_AXI_TIMER_1_BASEADDR + offset);
  } else if (num == XPAR_AXI_TIMER_2_DEVICE_ID) {
    return Xil_In32(XPAR_AXI_TIMER_2_BASEADDR + offset);
  }
}
// set the CASC bit to 1 and the UDT0 bit to 0 in the TCSR0 register (cascade
// mode and up counting).

// logic to set just one bit as a 1
static uint32_t setBitHigh(uint32_t value, int position) {
  uint32_t dummy = HEX_ONE;
  dummy = dummy << position;
  return value | dummy;
}

// logic to set just one bit as a 0
static uint32_t setBitLow(uint32_t value, int position) {
  uint32_t dummy = HEX_ONE;
  dummy = dummy << position;
  dummy = ~dummy;
  // set the CASC bit to 1 and the UDT0 bit to 0 in the TCSR0 register (cascade
  // mode and up counting).
  return value & dummy;
}

// reload the timer
void intervalTimer_reload(uint32_t timerNumber) {
  // writeRegister(timerNumber, TLR0, ZERO);
  writeRegister(timerNumber, TCSR0,
                setBitHigh(readRegister(timerNumber, TCSR0), LOAD0_BIT));
  writeRegister(timerNumber, TCSR0,
                setBitLow(readRegister(timerNumber, TCSR0), LOAD0_BIT));

  // writeRegister(timerNumber, TLR1, ZERO);
  writeRegister(timerNumber, TCSR1,
                setBitHigh(readRegister(timerNumber, TCSR1), LOAD0_BIT));
  writeRegister(timerNumber, TCSR1,
                setBitLow(readRegister(timerNumber, TCSR1), LOAD0_BIT));
}

// initialize the timers
void intervalTimer_initCountUp(uint32_t timerNumber) {
  writeRegister(timerNumber, TCSR0, ZERO); // write a 0 to the TCSR0 register.
  writeRegister(timerNumber, TCSR1, ZERO); // write a 0 to the TCSR1 register.

  writeRegister(timerNumber, TCSR0,
                setBitHigh(readRegister(timerNumber, TCSR0), CASC_BIT));
  writeRegister(timerNumber, TCSR0,
                setBitLow(readRegister(timerNumber, TCSR0), UDT0_BIT));

  writeRegister(timerNumber, TLR0, ZERO); // write a 0 to the TCSR0 register.
  writeRegister(timerNumber, TLR1, ZERO); // write a 0 to the TCSR1 register.

  // set the CASC bit to 1 and the UDT0 bit to 0 in the TCSR0 register (cascade
  // mode and up counting).

  intervalTimer_reload(timerNumber);
}

// set a bit high to start the timer
void intervalTimer_start(uint32_t timerNumber) {
  writeRegister(timerNumber, TCSR0,
                setBitHigh(readRegister(timerNumber, TCSR0), ENT0_BIT));
  writeRegister(timerNumber, TCSR1,
                setBitHigh(readRegister(timerNumber, TCSR0), ENT0_BIT));
}

// set a bit low to stop the timer
void intervalTimer_stop(uint32_t timerNumber) {
  writeRegister(timerNumber, TCSR0,
                setBitLow(readRegister(timerNumber, TCSR0), ENT0_BIT));
  writeRegister(timerNumber, TCSR1,
                setBitLow(readRegister(timerNumber, TCSR0), ENT0_BIT));
}

// convert the amount of ticks that the timer has recorded into seconds
double intervalTimer_getTotalDurationInSeconds(uint32_t timerNumber) {
  uint64_t stuff1 = readRegister(timerNumber, TCR0);
  uint64_t stuff2 = (uint64_t)readRegister(timerNumber, TCR1)
                    << BIT_SHIFT_FOR_SECONDS;
  uint64_t duration = stuff1 | stuff2;
  double time = (double)duration / XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ;
  return time;
}

// initialize the countdown timer
void intervalTimer_initCountDown(uint32_t timerNumber, double period) {
  writeRegister(timerNumber, TCSR0,
                setBitHigh(readRegister(timerNumber, TCSR0), CASC_BIT));
  // set the counter to go down
  writeRegister(timerNumber, TCSR0,
                setBitHigh(readRegister(timerNumber, TCSR0), UDT0_BIT));

  // write a 1 to the AHRT register.
  writeRegister(timerNumber, TCSR0,
                setBitHigh(readRegister(timerNumber, TCSR0), ARHT_BIT));

  // initialize the load registers with the right period
  writeRegister(timerNumber, TLR0, period * XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ);

  intervalTimer_reload(timerNumber);
}

// enable the interrupt
void intervalTimer_enableInterrupt(uint8_t timerNumber) {
  writeRegister(timerNumber, TCSR0,
                setBitHigh(readRegister(timerNumber, TCSR0), ENIT_BIT));
}
// disable the interrupt bit
void intervalTimer_disableInterrupt(uint8_t timerNumber) {
  writeRegister(timerNumber, TCSR0,
                setBitLow(readRegister(timerNumber, TCSR0), ENIT_BIT));
}

// acknowledge the interrupt for both TCSR 1 and 2
void intervalTimer_ackInterrupt(uint8_t timerNumber) {
  writeRegister(timerNumber, TCSR0,
                setBitHigh(readRegister(timerNumber, TCSR0), TINT_BIT));
  writeRegister(timerNumber, TCSR1,
                setBitHigh(readRegister(timerNumber, TCSR1), TINT_BIT));
}
