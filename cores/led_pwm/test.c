#include "test.h"

#include "led_pwm.h"

extern unsigned int err_cnt;

void test(void) {

	unsigned char led_o;

	unsigned int frequency = 500;
	unsigned int threshold_on = 200;
	unsigned int threshold_off = 300;

	unsigned char led = 0;

	for (int i = 0; i < 2 * frequency; i++) {

		led_pwm(led, threshold_on, threshold_off, &led_o);

		if (i < threshold_off && 0<<led != led_o)
			err_cnt++;
		if (i > threshold_off && i < frequency && 1<<led != led_o)
			err_cnt++;
		if (i > frequency && i < threshold_off + frequency && 0<<led != led_o)
			err_cnt++;
		if (i > threshold_off + frequency && i < 2 * frequency && 1<<led != led_o)
			err_cnt++;
	}
}
