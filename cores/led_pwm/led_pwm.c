#include <stdbool.h>

#include "led_pwm.h"

void led_pwm(unsigned char led, unsigned int threshold_on, unsigned int threshold_off, unsigned char *led_o) {
	static bool toggle = 0;
	static unsigned char led_states = 0;
	static unsigned int ticks = 0;

	if (threshold_on == ticks && toggle) {
		toggle = 0;
		ticks = 0;
	} else if (threshold_off == ticks && !toggle) {
		toggle = 1;
		ticks = 0;
	}

	if (0 == ticks) {
		led_states = (led_states & ~(1 << led)) | ((toggle << led) & (1 << led));
		*led_o = led_states;
	}

	ticks++;
}
