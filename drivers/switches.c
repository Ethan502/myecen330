#include "switches.h"

#include "xparameters.h"
#include "xil_io.h"

#define TRI_ADDR 0x0004
#define DATA_ADDR 0x0000
#define ALL_ONES 0x000F 

void switches_init()
{
    writeRegisterS(TRI_ADDR, ALL_ONES);
}

uint8_t switches_read()
{
    return readRegisterS(DATA_ADDR);
}

//function to automatically use the base address, so that I don't have to
//returns the register value as a 32bit uint
uint32_t readRegisterS(uint32_t offset) 
{
   return Xil_In32(XPAR_SLIDE_SWITCHES_BASEADDR + offset);
}

//function to write the given 32bit uint (value) to the register
void writeRegisterS(uint32_t offset, uint32_t value)
{
   Xil_Out32(XPAR_SLIDE_SWITCHES_BASEADDR + offset, value);
}
