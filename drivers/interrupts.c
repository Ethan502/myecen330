#include <stdio.h>
#include <xil_io.h>
#include <xparameters.h>
#include "armInterrupts.h"
#include "interrupts.h"

#define IPR_OFFSET 0x04
#define IER_OFFSET 0x08
#define IAR_OFFSET 0x0C
#define SIE_OFFSET 0x10
#define CIE_OFFSET 0x14
#define MER_OFFSET 0x1C

#define MER_INIT_VAL 0x03
#define ZEROS 0x00

#define NUM_OF_FCN_PTRS 3

static void (*isrFcnPtrs[NUM_OF_FCN_PTRS])() = {NULL};

//function to read the regester given the offset
static uint32_t readRegister(uint32_t offset)
{
  return Xil_In32(XPAR_AXI_INTC_0_BASEADDR + offset);
}

// function to write the given 32bit uint (value) to the register
static void writeRegister(uint32_t offset, uint32_t value) 
{
  Xil_Out32(XPAR_AXI_INTC_0_BASEADDR + offset, value);
}

static void interrupts_isr()
{
    int arraySize = sizeof(isrFcnPtrs)/sizeof(isrFcnPtrs[0]);
    sizeof(isrFcnPtrs)/sizeof(isrFcnPtrs[0]);
    for(int i = 0; i < arraySize; i++)
    {
        //see if a function has an interrupt pending
        if(readRegister(IPR_OFFSET) & (1 << i))
        {
            //check if there is a callback
            if(isrFcnPtrs[i] != NULL)
            {
                isrFcnPtrs[i]();
            }
            //acknowledge the interrupt
            writeRegister(IAR_OFFSET,1<<i);
        }
    }
}

//initialize the interrupt controller
void interrupts_init()
{
    print("in the init\n");
    writeRegister(MER_OFFSET,MER_INIT_VAL); //enable the interrupt output
    writeRegister(IER_OFFSET, ZEROS); //disables all interrupt input lines

    armInterrupts_init();
    armInterrupts_setupIntc(interrupts_isr);
    armInterrupts_enable();
}

//store a function in the isr
void interrupts_register(uint8_t irq, void (*fcn)())
{
    isrFcnPtrs[irq] = fcn;
}

void interrupts_irq_enable(uint8_t irq)
{
    writeRegister(SIE_OFFSET, 1 << irq);
}

void interrupts_irq_disable(uint8_t irq)
{
    writeRegister(CIE_OFFSET, 1 << irq);
}