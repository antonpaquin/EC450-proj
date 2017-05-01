/*
 * comm.h
 *
 *  Created on: Apr 30, 2017
 *      Author: wchen
 */

#ifndef COMM_H_
#define COMM_H_
#include "driverlib.h"

static volatile  uint8_t RXData[4];
static volatile unsigned int ii = 0;
static volatile unsigned jj=0;

void comm_setup();
#endif /* COMM_H_ */
