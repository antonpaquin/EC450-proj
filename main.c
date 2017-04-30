//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "driverlib.h"
#include "servo.h"

void main(void) {

    MAP_WDT_A_holdTimer();

    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    MAP_Interrupt_enableMaster();

    servo_setup();

    volatile uint32_t busyLoop;
    uint8_t servoPos = 0;
    while (1) {
        for (busyLoop = 0; busyLoop < 960000; busyLoop++) {}
        for (busyLoop = 0; busyLoop < 5; busyLoop++) {
            servo_set(busyLoop, servoPos);
        }
        servoPos = (servoPos + 30) % 180;
    }

}
