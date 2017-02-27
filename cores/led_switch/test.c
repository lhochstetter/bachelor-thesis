#include <stdbool.h>

#include "test.h"

#include "led_switch.h"

extern unsigned int err_cnt;

void test(void) {

	unsigned char expected_result = 0;
	bool state;
	unsigned char led_o;

	for (int i = 0; i < 8; i++) {
		state = 1;
		expected_result = 1 << i;
		led_switch(i, state, &led_o);

		if (expected_result != led_o)
			err_cnt++;

		for (int j = 0; j < 8; j++) {
			if (i != j) {
				expected_result += 1 << j;
				led_switch(j, state, &led_o);
				if (expected_result != led_o)
					err_cnt++;
				}
			}

		state = 0;
		for (int k = 0; k < 8; k++) {
			if (i != k) {
				expected_result -= 1 << k;
				led_switch(k, state, &led_o);
				if (expected_result != led_o)
					err_cnt++;
				}
		}
		expected_result -= 1 << i;
		led_switch(i, state, &led_o);

		if (expected_result != led_o)
			err_cnt++;
	}
}
