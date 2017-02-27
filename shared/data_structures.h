#ifndef data_structures_h
#define data_structures_h

#include <stdbool.h>

enum controller_mode {
	CONSTANT = 0,
	EXT_SWITCH,
	PWM
};

struct led_config {
	enum controller_mode mode;
	bool reset;
	bool initial_value;
	unsigned int threshold_on;
	unsigned int threshold_off;
};

#endif
