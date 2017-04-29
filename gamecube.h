/*
 * gamecube.h
 *
 *  Created on: Apr 19, 2017
 *      Author: anton
 */

#ifndef GAMECUBE_H_
#define GAMECUBE_H_

#include <inttypes.h>

typedef struct gc_input_t gc_input_t;

#define GC_RELEASED 0
#define GC_PRESSED 255

gc_input_t* gc_init();
void gc_cleanup(gc_input_t*);

void gc_set_joy_x(gc_input_t*, uint8_t);
void gc_set_joy_y(gc_input_t*, uint8_t);
void gc_set_cstick_x(gc_input_t*, uint8_t);
void gc_set_cstick_y(gc_input_t*, uint8_t);
void gc_set_shoulder_l(gc_input_t*, uint8_t);
void gc_set_shoulder_r(gc_input_t*, uint8_t);
void gc_set_start(gc_input_t*, char);
void gc_set_y(gc_input_t*, char);
void gc_set_x(gc_input_t*, char);
void gc_set_b(gc_input_t*, char);
void gc_set_a(gc_input_t*, char);
void gc_set_l(gc_input_t*, char);
void gc_set_r(gc_input_t*, char);
void gc_set_z(gc_input_t*, char);
void gc_set_dpad_up(gc_input_t*, char);
void gc_set_dpad_left(gc_input_t*, char);
void gc_set_dpad_down(gc_input_t*, char);
void gc_set_dpad_right(gc_input_t*, char);


#endif /* GAMECUBE_H_ */
