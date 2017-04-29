//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "gamecube.h"
#include "transfer.h"

void main(void) {
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    // Set clockspeed to something fast enough
    CS -> KEY |=  0x695A; // Clock key enables clock modification
    CS -> CTL0 |= BIT(18); CS -> CTL0 &= ~(BIT(17)); CS -> CTL0 |= BIT(16); // DCO to max speed
    CS -> CTL1 &= ~BIT2; CS -> CTL1 |= BIT1; CS -> CTL1 |= BIT0; // Set mclk to DCO


    // Set up a gpio interrupt
    P4 -> DIR &= ~BIT5; // Set p4, 5 as an input
    P4 -> IES &= ~BIT5; // Interrupt on posedge
    P4 -> IE |= BIT5; // Set p4 5 interrupt on
    NVIC -> ISER[0] = 1 << ((PORT4_IRQn) & 31); // P4 interrupt in NVIC


    // Build a gc input
    struct gc_input_t* simpleInput = gc_init();

    // Put the gc input in the buffer
    tf_putBuffer(simpleInput);
}

// Attach gpio interrupt to transfer.c
void PORT4_IRQHandler(void) {
    tf_onGpioInterrupt()
}
