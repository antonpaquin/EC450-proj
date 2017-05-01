/*
 * comm.c
 *
 *  Created on: Apr 30, 2017
 *      Author: wchen
 */


#include "comm.h"
#include "servo.h"
uint32_t status = 0 ;
static volatile unsigned int ii = 0;
static volatile unsigned char RXData[4];
const eUSCI_SPI_SlaveConfig spiSlaveConfig = {
   EUSCI_B_SPI_LSB_FIRST,
   //EUSCI_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
   EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
   EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW,
   EUSCI_B_SPI_3PIN
   };
void EUSCIB0_IRQHandler(void)
{

    status = SPI_getEnabledInterruptStatus(EUSCI_B0_BASE);
    SPI_clearInterruptFlag(EUSCI_B0_BASE, status);

    if(status & EUSCI_B_SPI_RECEIVE_INTERRUPT)
    {
        RXData[ii++] = SPI_receiveData(EUSCI_B0_BASE);
        if (ii == 4) {

                        printf("Setting servos\n");

                        unsigned char servoValues[5];
                        servoValues[0] = RXData[0];
                        servoValues[1] = 180 - RXData[0];
                        servoValues[2] = RXData[1];
                        servoValues[3] = RXData[2];
                        servoValues[4] = RXData[3];
                               for (jj = 0; jj < 5; jj++) {
                                   servo_set(jj, servoValues[jj]);

                               }


                for(jj=0;jj<4;jj++){RXData[jj]=0;};
                ii = 0;
        }



    }

};
void comm_setup(){
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7,GPIO_PRIMARY_MODULE_FUNCTION);
    SPI_initSlave(EUSCI_B0_BASE, &spiSlaveConfig);
    SPI_enableModule(EUSCI_B0_BASE);
    SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_RECEIVE_INTERRUPT);
   // SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);
    Interrupt_enableInterrupt(INT_EUSCIB0);
    Interrupt_enableSleepOnIsrExit();

    //probably the same?
    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();
}
