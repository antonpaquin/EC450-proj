//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "driverlib.h"

Timer_A_PWMConfig pwmConfig = {
    TIMER_A_CLOCKSOURCE_SMCLK,
    TIMER_A_CLOCKSOURCE_DIVIDER_1,
    240000,
    TIMER_A_CAPTURECOMPARE_REGISTER_1,
    TIMER_A_OUTPUTMODE_RESET_SET,
    12000
};

void main(void) {

    MAP_WDT_A_holdTimer();

    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);

    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();

    /* Sleeping when not in use */
    while (1)
    {
    MAP_PCM_gotoLPM0();
    }
    }

    /* Port1 ISR - This ISR will progressively step up the duty cycle of the PWM
    * on a button press
    */
    void PORT1_IRQHandler(void)
    {
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    if (status & GPIO_PIN1)
    {
    if(pwmConfig.dutyCycle == 36000)
    pwmConfig.dutyCycle = 12000;
    else
    pwmConfig.dutyCycle += 6000;

    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    }
    }
