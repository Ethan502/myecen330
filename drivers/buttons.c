#include "xparameters.h"
#include "xil_io.h"

#include "buttons.h"

#define TRI_ADDR 0x0004
#define DATA_ADDR 0x0000
#define ALL_ONES 0x000F 

void buttons_init()
{
   writeRegisterB(TRI_ADDR, ALL_ONES);
}

uint8_t buttons_read()
{
   return readRegisterB(DATA_ADDR);
}

//function to automatically use the base address, so that I don't have to
//returns the register value as a 32bit uint
uint32_t readRegisterB(uint32_t offset) 
{
   return Xil_In32(XPAR_PUSH_BUTTONS_BASEADDR + offset);
}

//function to write the given 32bit uint (value) to the register
void writeRegisterB(uint32_t offset, uint32_t value)
{
   Xil_Out32(XPAR_PUSH_BUTTONS_BASEADDR + offset, value);
}
