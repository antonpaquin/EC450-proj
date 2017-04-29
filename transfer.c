/*
 * transfer.c
 *
 *  Created on: Apr 19, 2017
 *      Author: anton
 */

#include <stdlib.h>
#include "msp.h"

#include "gamecube.h"

gc_input_t* nextInput;
void tf_putBuffer(gc_input_t* input) {
    nextOutput = input;
}

void tf_onGpioInterrupt() {
    // clear interrupt
    P4 -> IFG &= ~BIT5;

    // disable interrupts
    P4 -> IE &= ~BIT5;
    //__disable_interrupt();

    if (!nextOutput)
        return;

    // wait 24 (tuned) cycles
    volatile int timer = 0;
    for (timer=0; timer<24; timer++) {
    }

    // set pin direction to out
    P4 -> DIR |= BIT5;

    char* writebuf = (char*) nextInput;
    char writePosition = 0;
    char toSend;
    for (writePosition=0; writePosition<64; writePosition++) {
        toSend = (*(writebuf + writePosition / 8)) & (1 << (writePosition % 8)); // (128 >> ?) to reverse bit order
        tf_send(1);
        tf_send(toSend);
        tf_send(toSend);
        tf_send(0);
        // possibly include delay code here
    }
    nextInput = NULL;

    // set pin direction to in
    P4 -> DIR &= ~BIT5;
    // enable interrupts
    P4 -> IE |= BIT5;
}

inline void tf_send(char c) {
    if (c) {
        P4 -> OUT |= BIT5;
    } else {
        P4 -> OUT &= ~BIT5;
    }
}
