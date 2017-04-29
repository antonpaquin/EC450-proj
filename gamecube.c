/*
 * gamecube.c
 *
 *  Created on: Apr 19, 2017
 *      Author: anton
 */

#include <stdlib.h>

#include "msp.h"

#include "gamecube.h"

#define bitset(byte, bit, val) \
    switch(val) { \
    case GC_PRESSED: \
        byte |= (val & BIT(bit)); \
        break; \
    case GC_RELEASED: \
        byte &= ~(val & BIT(bit)); \
        break; \
    }

typedef struct gc_input_t {
    uint8_t b0;
    uint8_t b1;
    uint8_t joyx;
    uint8_t joyy;
    uint8_t cx;
    uint8_t cy;
    uint8_t l;
    uint8_t r;
} gc_input_t;

gc_input_t* gc_init() {
    struct gc_input_t* res = (struct gc_input_t*) malloc(sizeof(gc_input_t));
    res -> b0 = 0;
    res -> b1 = 1;
    res -> joyx = 128;
    res -> joyy = 128;
    res -> cx = 128;
    res -> cy = 128;
    res -> l = 0;
    res -> r = 0;
    return res;
}

void gc_cleanup(gc_input_t* self) {
    free(self);
}

void gc_set_joy_x      (gc_input_t* self, uint8_t value) { self -> joyx = value; }
void gc_set_joy_y      (gc_input_t* self, uint8_t value) { self -> joyy = value; }
void gc_set_cstick_x   (gc_input_t* self, uint8_t value) { self -> cx = value;   }
void gc_set_cstick_y   (gc_input_t* self, uint8_t value) { self -> cy = value;   }
void gc_set_shoulder_l (gc_input_t* self, uint8_t value) { self -> l = value;    }
void gc_set_shoulder_r (gc_input_t* self, uint8_t value) { self -> r = value;    }

void gc_set_start      (gc_input_t* self, char value) { bitset(self -> b0, 3, value); }
void gc_set_y          (gc_input_t* self, char value) { bitset(self -> b0, 4, value); }
void gc_set_x          (gc_input_t* self, char value) { bitset(self -> b0, 5, value); }
void gc_set_b          (gc_input_t* self, char value) { bitset(self -> b0, 6, value); }
void gc_set_a          (gc_input_t* self, char value) { bitset(self -> b0, 7, value); }
void gc_set_l          (gc_input_t* self, char value) { bitset(self -> b1, 1, value); }
void gc_set_r          (gc_input_t* self, char value) { bitset(self -> b1, 2, value); }
void gc_set_z          (gc_input_t* self, char value) { bitset(self -> b1, 3, value); }
void gc_set_dpad_up    (gc_input_t* self, char value) { bitset(self -> b1, 4, value); }
void gc_set_dpad_left  (gc_input_t* self, char value) { bitset(self -> b1, 5, value); }
void gc_set_dpad_down  (gc_input_t* self, char value) { bitset(self -> b1, 6, value); }
void gc_set_dpad_right (gc_input_t* self, char value) { bitset(self -> b1, 7, value); }
