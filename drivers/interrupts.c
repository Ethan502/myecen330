#include "interrupts.h"
#include "armInterrupts.h"
#include <stdio.h>
#include <xil_io.h>
#include <xparameters.h>

#define IPR_OFFSET 0x04
#define IER_OFFSET 0x08
#define IAR_OFFSET 0x0C
#define SIE_OFFSET 0x10
#define CIE_OFFSET 0x14
#define MER_OFFSET 0x1C

#define MER_INIT_VAL 0x03
#define ZEROS 0x00
#define ZERO_INDEX 0
#define SHIFT_NUM 1

#define NUM_OF_FCN_PTRS 3

// global variable for the array of function pointers
static void (*isrFcnPtrs[NUM_OF_FCN_PTRS])() = {NULL};

// function to read the regester given the offset
static uint32_t readRegister(uint32_t offset) {
  return Xil_In32(XPAR_AXI_INTC_0_BASEADDR + offset);
}

// function to write the given 32bit uint (value) to the register
static void writeRegister(uint32_t offset, uint32_t value) {
  Xil_Out32(XPAR_AXI_INTC_0_BASEADDR + offset, value);
}

// go through the fcnptr list and activate them if they are still pending
static void interrupts_isr() {
  int arraySize = sizeof(isrFcnPtrs) / sizeof(isrFcnPtrs[ZERO_INDEX]);
  sizeof(isrFcnPtrs) / sizeof(isrFcnPtrs[ZERO_INDEX]);
  for (int i = ZERO_INDEX; i < arraySize; i++) {
    // see if a function has an interrupt pending
    if (readRegister(IPR_OFFSET) & (SHIFT_NUM << i)) {
      // check if there is a callback
      if (isrFcnPtrs[i] != NULL) {
        isrFcnPtrs[i]();
      }
      // acknowledge the interrupt
      writeRegister(IAR_OFFSET, SHIFT_NUM << i);
    }
  }
}

// initialize the interrupt controller
void interrupts_init() {
  writeRegister(MER_OFFSET, MER_INIT_VAL); // enable the interrupt output
  writeRegister(IER_OFFSET, ZEROS);        // disables all interrupt input lines

  armInterrupts_init();
  armInterrupts_setupIntc(interrupts_isr);
  armInterrupts_enable();

  writeRegister(IER_OFFSET, ZEROS);
}

// store a function in the isr
void interrupts_register(uint8_t irq, void (*fcn)()) { isrFcnPtrs[irq] = fcn; }

// enable the irq
void interrupts_irq_enable(uint8_t irq) {
  writeRegister(SIE_OFFSET, SHIFT_NUM << irq);
}

// disable the irq
void interrupts_irq_disable(uint8_t irq) {
  writeRegister(CIE_OFFSET, SHIFT_NUM << irq);
}