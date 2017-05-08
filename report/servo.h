/*
 * servo.h
 *
 *  Created on: Apr 29, 2017
 *      Author: anton
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

// Valid ids are 0 - 4
// Valid positions are 0 - 180
void servo_set(uint8_t id, uint8_t pos);
void servo_setup();

#endif /* SERVO_H_ */
