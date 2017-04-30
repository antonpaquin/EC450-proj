/*
 * comm.h
 *
 *  Created on: Apr 30, 2017
 *      Author: wchen
 */

#ifndef COMM_H_
#define COMM_H_
#include "driverlib.h"

static volatile uint8_t RXData[10];
static volatile uint8_t i = 0;

void comm_setup();
#endif /* COMM_H_ */
