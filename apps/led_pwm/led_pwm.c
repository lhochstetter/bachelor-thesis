#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

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

int main(int argc, char** argv) 
{

	const int base_addr = 0x83C10000; // end: 0x83C10FFF
	const int size      = 0x1000;     // 4k

	volatile struct led_core {
		uint32_t control;
		uint32_t reserved_0x04;
		uint32_t reserved_0x08;
		uint32_t reserved_0x0c;
		uint32_t led;
		uint32_t reserved_0x14;
		uint32_t threshold_on;
		uint32_t reserved_0x1c;
		uint32_t threshold_off;
		uint32_t reserved_0x24;
	} *core;

	int map_file = 0;

	map_registers(&map_file, (void **) &core, base_addr, size);

	/* blink LED 1 at 1Hz */
	(*(volatile uint32_t *)(&core->led)) = 0x0001;
	(*(volatile uint32_t *)(&core->threshold_on))  = 90000000;
	(*(volatile uint32_t *)(&core->threshold_off)) = 10000000;

	/* start core and enable auto restart */
	(*(volatile uint32_t *)(&core->control)) |= 0x080;
	(*(volatile uint32_t *)(&core->control)) |= 0x001;

	getchar();

	/* stop core and disable auto restart */
	(*(volatile uint32_t *)(&core->control)) &= 0xFF7E;

	clean_up(map_file);

	return 0;
}
