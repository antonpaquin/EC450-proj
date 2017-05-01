//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "driverlib.h"
#include "servo.h"
#include "comm.h"

static unsigned char data_start = 127;
#define data_end 136
volatile uint32_t busyLoop;
uint8_t servoPos = 0;


void main(void) {

    MAP_WDT_A_holdTimer();

    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    MAP_Interrupt_enableMaster();

    servo_setup();

    comm_setup();






    while (1) {
        __sleep();

    }

}
