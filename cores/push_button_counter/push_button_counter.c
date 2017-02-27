#include <stdbool.h>

#include "push_button_counter.h"

void push_button_counter(bool inc_i, bool dec_i, unsigned char *led_o) {

	static bool pos_edge_inc[2] = {1, 1};
	static bool pos_edge_dec[2] = {1, 1};

	static unsigned char value = 0;

	pos_edge_inc[1] = pos_edge_inc[0];
	pos_edge_inc[0] = inc_i;

	pos_edge_dec[1] = pos_edge_dec[0];
	pos_edge_dec[0] = dec_i;

	if (pos_edge_inc[0] && !pos_edge_inc[1] && dec_i && 255 > value) {
		value += 1;
		*led_o = value;
	} else if (pos_edge_dec[0] && !pos_edge_dec[1] && inc_i && 0 < value) {
		value -= 1;
		*led_o = value;
	}
}
