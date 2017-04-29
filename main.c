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

    // Set timer to something fast enough

    // Set up a gpio interrupt
}

// Attach gpio interrupt to transfer.c
