#include "xparameters.h"
#include "xil_io.h"

#define TCSR0 0x0000
#define TLR0 0x0004
#define TCR0 0x0008

#define TCSR1 0x000A
#define TLR1 0x000E
#define TCR1 0x0012

#define ZERO 0
#define HEX_ONE 0x0001

#define CASC_BIT 0x000B
#define UDT0_BIT 0x0001
#define LOAD0_BIT 0x0005
#define ENT0_BIT 0x0007

//cascade is 11 and udt0 is 1
static void writeRegister(uint32_t num, uint32_t offset, uint32_t value)
{
    if(num == XPAR_AXI_TIMER_0_DEVICE_ID){Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + offset, value);}
    else if(num == XPAR_AXI_TIMER_1_DEVICE_ID){Xil_Out32(XPAR_AXI_TIMER_1_BASEADDR + offset, value);}
    else if(num == XPAR_AXI_TIMER_2_DEVICE_ID){Xil_Out32(XPAR_AXI_TIMER_2_BASEADDR + offset, value);}
}

//read the values at the register of the inputed timer id number
static uint32_t readRegister(uint32_t num, uint32_t offset)
{
    if(num == XPAR_AXI_TIMER_0_DEVICE_ID){return Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + offset);}
    else if(num == XPAR_AXI_TIMER_1_DEVICE_ID){return Xil_Int32(XPAR_AXI_TIMER_1_BASEADDR + offset);}
    else if(num == XPAR_AXI_TIMER_2_DEVICE_ID){return Xil_In32(XPAR_AXI_TIMER_2_BASEADDR + offset);}
}

//logic to set just one bit as a 1
static uint32_t setBitHigh(uint32_t value, int position)
{
    uint32_t dummy = HEX_ONE;
    dummy = dummy << position;
    return value | dummy;
}

//logic to set just one bit as a 0
static uint32_t setBitLow(uint32_t value, int position)
{
    uint32_t dummy = HEX_ONE;
    dummy = dummy << position;
    dummy = ~dummy;
    return value & dummy;
}

//initialize the timers
void intervalTimer_initCountUp(uint32_t timerNumber)
{
    writeRegister(timerNumber,TCSR0,ZERO); // write a 0 to the TCSR0 register.
    writeRegister(timerNumber,TCSR1,ZERO); // write a 0 to the TCSR1 register.
    
    // set the CASC bit to 1 and the UDT0 bit to 0 in the TCSR0 register (cascade mode and up counting).
    writeRegister(timerNumber,TCSR0,setBitHigh(readRegister0(timerNumber,TCSR0),CASC_BIT));
    writeRegister(timerNumber,TCSR0,setBitLow(readRegister0(timerNumber,TCSR0),UDT0_BIT)); 

    intervalTimer_reload(timerNumber);
}

//reset the timer
void intervalTimer_reload(uint32_t timerNumber)
{
    writeRegister(timerNumber,TLR0,ZERO);
    writeRegister(timerNumber,TCSR0,setBitHigh(readRegister(timerNumber,TCSR0),LOAD0_BIT));
    writeRegister(timerNumber,TCSR0,setBitLow(readRegister(timerNumber,TCSR0),LOAD0_BIT));

    writeRegister(timerNumber,TLR1,ZERO);
    writeRegister(timerNumber,TCSR1,setBitHigh(readRegister(timerNumber,TCSR1),LOAD0_BIT));
    writeRegister(timerNumber,TCSR1,setBitLow(readRegister(timerNumber,TCSR1),LOAD0_BIT));
}

//set a bit high to start the timer
void intervalTimer_start(uint32_t timerNumber)
{
    writeRegister(timerNumber,TCSR0,setBitHigh(readRegister(timerNumber,TCSR0),ENT0_BIT));
}

void intervalTimer_stop(uint32_t timerNumber)
{
    writeRegister(timerNumber,TCSR0,setBitLow(readRegister(timerNumber,TCSR0),ENT0_BIT));
}

double intervalTimer_getTotalDurationInSeconds(uint32_t timerNumber)
{
    uint32_t stuff = readRegister(timerNumber, TCR0);
    
}
