#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#include "data_structures.h"

int map_registers(int *fd, void **c, int c_addr, int c_size)
{
	if ((*fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
		fprintf(stderr, "Error: could not open /dev/mem!\n");
		return -1;
	}

	if ((*c = mmap(NULL, c_size, PROT_READ | PROT_WRITE,
		MAP_SHARED, *fd, c_addr)) == (void *) -1) {

		fprintf(stderr, "Error: could not map memory to file!\n");
		return -1;
	}

	return 0;
}

int clean_up(int fd)
{
	if (close(fd) < 0) {
		fprintf(stderr, "Error: could not close map file!\n");
		return -1;
	}
	return 0;
}
/**
 * IP Core register
 * [0]  -> control signals
 * [1]  -> global interrupt enable
 * [2]  -> IP interrupt enable
 * [3]  -> IP interrupt status
 * ---------------------------------- global_offset = 4
 * [4]  -> config initial value
 * [6]  -> config reset
 * [8]  -> config current mode
 * [10] -> config threshold on
 * [12] -> config threshold off
 * [13] -> config end
 * ---------------------------------- led_offset = 10
 * formular global_offset + led * led_offset
 */
void configure_led(volatile uint32_t *core,
			unsigned char led,
			enum controller_mode mode,
			bool initial_value,
			unsigned int threshold_on,
			unsigned int threshold_off
		)
{
	unsigned int position = 4 + led * 10;

	(*(volatile uint32_t *)(&core[position])) = initial_value;
	(*(volatile uint32_t *)(&core[position + 2])) = 0;
	(*(volatile uint32_t *)(&core[position + 4])) = mode;
	(*(volatile uint32_t *)(&core[position + 6])) = threshold_on;
	(*(volatile uint32_t *)(&core[position + 8])) = threshold_off;
}

int main(int argc, char** argv)
{

	const int base_addr = 0x43C00000; // end: 0x43000FFF
	const int size      = 0x1000;     // 4k

	uint32_t *core;

	int map_file = 0;

	map_registers(&map_file, (void **) &core, base_addr, size);

	/* configure leds */
	configure_led(core, 0, PWM, 1, 50000000, 50000000);
	configure_led(core, 1, PWM, 1, 50000000, 50000000);
	configure_led(core, 2, PWM, 1, 50000000, 50000000);
	configure_led(core, 3, PWM, 1, 50000000, 50000000);
	configure_led(core, 4, PWM, 0, 50000000, 50000000);
	configure_led(core, 5, PWM, 0, 50000000, 50000000);
	configure_led(core, 6, PWM, 0, 50000000, 50000000);
	configure_led(core, 7, PWM, 0, 50000000, 50000000);

	/* start core and enable auto restart */
	(*(volatile uint32_t *)(&core[0])) |= 0x080;
	(*(volatile uint32_t *)(&core[0])) |= 0x001;

	getchar();

	/* stop execution */
	(*(volatile uint32_t *)(&core[4 + 0 * 10 + 2])) = 1;
	(*(volatile uint32_t *)(&core[4 + 1 * 10 + 2])) = 1;
	(*(volatile uint32_t *)(&core[4 + 2 * 10 + 2])) = 1;
	(*(volatile uint32_t *)(&core[4 + 3 * 10 + 2])) = 1;
	/* reconfigure */
	configure_led(core, 0, EXT_SWITCH, 0, 0, 0);
	configure_led(core, 1, EXT_SWITCH, 0, 0, 0);
	configure_led(core, 2, EXT_SWITCH, 0, 0, 0);
	configure_led(core, 3, EXT_SWITCH, 0, 0, 0);

	/* resume execution */
	(*(volatile uint32_t *)(&core[4 + 0 * 10 + 2])) = 0;
	(*(volatile uint32_t *)(&core[4 + 1 * 10 + 2])) = 0;
	(*(volatile uint32_t *)(&core[4 + 2 * 10 + 2])) = 0;
	(*(volatile uint32_t *)(&core[4 + 3 * 10 + 2])) = 0;

	getchar();

	/* stop core and disable auto restart */
	(*(volatile uint32_t *)(&core[0])) &= 0xFF7E;

	clean_up(map_file);

	return 0;
}
