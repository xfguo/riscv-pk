
#include <stdint.h>
#include "init.h"

volatile uint64_t tohost __attribute__((aligned(64)));
volatile uint64_t fromhost __attribute__((aligned(64)));

static long htif_tohost(long which, long arg0, long arg1, long arg2)
{
	volatile uint64_t magic_mem[8] __attribute__((aligned(64)));
	uint64_t oldfromhost;
	magic_mem[0] = which;
	magic_mem[1] = arg0;
	magic_mem[2] = arg1;
	magic_mem[3] = arg2;
	__sync_synchronize();
	tohost = (long) magic_mem;
	do
	{
		oldfromhost = fromhost;
		fromhost = 0;
	} while (oldfromhost == 0);
	return magic_mem[0];
}

void init(void) {
	const char hello[] = "Hello World\n";

	htif_tohost(64, 1, (long) hello, sizeof(hello));
	while(1) {
		
	}
}
