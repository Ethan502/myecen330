#include "xparameters.h"
#include "xil_io.h"

#include "buttons.h"

void buttons_init()
{
    //the while loop will keep the driver constantly refreshing
    while(1)
    {
        

    }
}

//function to automatically use the base address, so that I don't have to
//returns the register value as a 32bit uint
uint32_t readRegister(uint32_t offset) 
{
   return Xil_In32(XPAR_PUSH_BUTTONS_BASEADDR + offset);
}

//function to write the given 32bit uint (value) to the register
void writeRegister(uint32_t offset, uint32_t value)
{
   Xil_Out32(XPAR_PUSH_BUTTONS_BASEADDR + offset, value);
}
