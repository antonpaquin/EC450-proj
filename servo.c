/*
 * servo.c
 *
 *  Created on: Apr 29, 2017
 *      Author: anton
 */

#include "msp.h"
#include "driverlib.h"

#define servo_min 3000
#define servo_max 36000
#define servo_step ((servo_max - servo_min) / 180)

#define SERVCONF(ccr) { \
        TIMER_A_CLOCKSOURCE_SMCLK, \
        TIMER_A_CLOCKSOURCE_DIVIDER_1, \
        240000, \
        TIMER_A_CAPTURECOMPARE_REGISTER_ ## ccr, \
        TIMER_A_OUTPUTMODE_RESET_SET, \
        0 \
    }

Timer_A_PWMConfig servo_confs[]  = {
    SERVCONF(1), // TA1
    SERVCONF(1),
    SERVCONF(2),
    SERVCONF(2), // TA1
    SERVCONF(4)
};

void servo_set(uint8_t id, uint8_t pos) {
    if (pos > 180)
        return;
    if (id > 4)
        return;
    servo_confs[id].dutyCycle = servo_min + (servo_step * pos);
    if (id==0 || id==3) {
        MAP_Timer_A_generatePWM(TIMER_A1_BASE, servo_confs + id);
    } else {
        MAP_Timer_A_generatePWM(TIMER_A0_BASE, servo_confs + id);
    }
}

void servo_setup() {
    // Godammit driverlib
    PMAPKEYID = 0x02D52;

    P2MAP -> PMAP_REGISTER4 = 20; P2MAP -> PMAP_REGISTER5 = 21; P2MAP -> PMAP_REGISTER7 = 23;
    uint8_t p2bits = BIT4 | BIT5 | BIT7;
    P2->DIR |= p2bits; P2->SEL1 &= ~p2bits; P2->SEL0 |= p2bits;

    P7MAP->PMAP_REGISTER7 = 24; P7MAP->PMAP_REGISTER6 = 25;
    uint8_t p7bits = BIT6 | BIT7;
    P7->DIR |= p7bits; P7->SEL1 &= ~p7bits; P7->SEL0 |= p7bits;

    PMAPKEYID = 0;


    MAP_Timer_A_generatePWM(TIMER_A1_BASE, servo_confs + 0);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, servo_confs + 1);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, servo_confs + 2);
    MAP_Timer_A_generatePWM(TIMER_A1_BASE, servo_confs + 3);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, servo_confs + 4);
}
