/*
 * transfer.c
 *
 *  Created on: Apr 19, 2017
 *      Author: anton
 */

#include <stdlib.h>

#include "gamecube.h"

gc_input_t* nextInput;
void tf_putBuffer(gc_input_t* input) {
    nextOutput = input;
}

void tf_onGpioInterrupt() {
    // clear interrupt
    // disable interrupts

    if (!nextOutput)
        return;

    // wait 24 (tuned) cycles

    // set pin direction to out

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
    // enable interrupts
}

inline void tf_send(char c) {
    if (c) {
        // write 1
    } else {
        // write 0
    }
}
