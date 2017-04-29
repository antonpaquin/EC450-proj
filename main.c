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

    // Set up a gpio interrupt

    // Build a gc input

    // Put the gc input in the buffer
}

// Attach gpio interrupt to transfer.c
