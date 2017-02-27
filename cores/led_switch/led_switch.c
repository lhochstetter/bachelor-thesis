#include <stdbool.h>

#include "led_switch.h"

void led_switch(unsigned char led, bool state, unsigned char *led_o)
{
	static unsigned char led_states = 0;
	led_states = (led_states & ~(1 << led)) | ((state << led) & (1 << led));
	*led_o = led_states;
}
