/*
 * servo.c
 *
 *  Created on: Apr 29, 2017
 *      Author: anton
 */

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
        (servo_max + servo_min) / 2 \
    }

Timer_A_PWMConfig servo_confs[]  = {
    SERVCONF(0),
    SERVCONF(1),
    SERVCONF(2),
    SERVCONF(3),
    SERVCONF(4)
};

void servo_set(uint8_t id, uint8_t pos) {
    if (pos > 180)
        return;
    if (id > 4)
        return;
    servo_confs[id].dutyCycle = servo_min + (servo_step * pos);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, servo_confs + id);
}

void servo_setup() {
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    MAP_Timer_A_generatePWM(TIMER_A0_BASE, servo_confs + 0);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, servo_confs + 1);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, servo_confs + 2);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, servo_confs + 3);
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, servo_confs + 4);
}
