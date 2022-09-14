#include "switches.h"

#include "xil_io.h"
#include "xparameters.h"

#define TRI_ADDR 0x0004
#define DATA_ADDR 0x0000
#define ALL_ONES 0x000F

// function to automatically use the base address, so that I don't have to
// returns the register value as a 32bit uint
static uint32_t readRegisterS(uint32_t offset) {
  return Xil_In32(XPAR_SLIDE_SWITCHES_BASEADDR + offset);
}

// function to write the given 32bit uint (value) to the register
static void writeRegisterS(uint32_t offset, uint32_t value) {
  Xil_Out32(XPAR_SLIDE_SWITCHES_BASEADDR + offset, value);
}

// init the tri register on the switches
void switches_init() { writeRegisterS(TRI_ADDR, ALL_ONES); }

// read the switches
uint8_t switches_read() { return readRegisterS(DATA_ADDR); }


