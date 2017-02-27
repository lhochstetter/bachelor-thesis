#ifndef led_controller_h
#define led_controller_h

#define LED_COUNT 8

#include "data_structures.h"

extern struct led_config config[LED_COUNT];

extern bool gp_i[LED_COUNT];

extern bool led_o[LED_COUNT];

void led_controller();

#endif
