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
		uint32_t g_interrupt_enable;
		uint32_t ip_interrupt_enable;
		uint32_t ip_interrupt_status;
	} *core;

	int map_file = 0;

	map_registers(&map_file, (void **) &core, base_addr, size);

	/* start core and enable auto restart */
	(*(volatile uint32_t *)(&core->control)) |= 0x080;
	(*(volatile uint32_t *)(&core->control)) |= 0x001;

	getchar();

	/* stop core and disable auto restart */
	(*(volatile uint32_t *)(&core->control)) &= 0xFF7E;

	clean_up(map_file);

	return 0;
}
