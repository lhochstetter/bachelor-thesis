#include <stdbool.h>

#include "data_structures.h"

#include "led_controller.h"

extern struct led_config config[LED_COUNT];

bool gp_i[LED_COUNT];

bool led_o[LED_COUNT];

static struct {
	bool toggle;
	bool pos_edge[2];
	enum {
		INIT = 0,
		RUNNING,
		HALT
	} state;
	unsigned int ticks;
} handles[LED_COUNT];

void handle(unsigned char i)
{
	switch (handles[i].state) {
	case INIT:
		handles[i].toggle = config[i].initial_value;
		handles[i].pos_edge[0] = 1;
		handles[i].pos_edge[1] = 1;
		handles[i].ticks = 0;
		handles[i].state = RUNNING;
		break;
	case RUNNING:
		if (config[i].reset) {
			handles[i].state = HALT;
		} else {
			switch (config[i].mode) {
			case CONSTANT:
				break;
			case EXT_SWITCH:
				handles[i].pos_edge[1] = handles[i].pos_edge[0];
				handles[i].pos_edge[0] = gp_i[i];
					if (handles[i].pos_edge[0] && !handles[i].pos_edge[1] && handles[i].toggle)
						handles[i].toggle = 0;
					else if (handles[i].pos_edge[0] && !handles[i].pos_edge[1] && !handles[i].toggle)
						handles[i].toggle = 1;
				break;
			case PWM:
				if (config[i].threshold_on == handles[i].ticks && handles[i].toggle) {
					handles[i].toggle = 0;
					handles[i].ticks = 0;
				} else if (config[i].threshold_off == handles[i].ticks && !handles[i].toggle) {
					handles[i].toggle = 1;
					handles[i].ticks = 0;
				}
				handles[i].ticks++;
				break;
			default:
				break;
			}
		}
		break;
	case HALT:
		if (!config[i].reset)
			handles[i].state = INIT;
		break;
	default:
		break;
	}
	led_o[i] = handles[i].toggle;
}

void led_controller()
{

LOOP:	for (unsigned char i = 0; i < LED_COUNT; i++)
		handle(i);

}
