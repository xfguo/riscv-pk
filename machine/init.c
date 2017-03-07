
#include <stdint.h>
#include "encoding.h"
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

volatile uint64_t* mtime;
volatile uint64_t* mtimecmp;

void timer_interrupt(void) {
	const char hello[] = "Timer\n";
	
	clear_csr(mip, MIP_MTIP);

	htif_tohost(64, 1, (long) hello, sizeof(hello));
	
	*mtimecmp = *mtime + 138727004;
}

void init(void) {
	const char hello[] = "Hello World\n";

	mtime = (uint64_t *)0x40000000;
	mtimecmp = (uint64_t *)0x40000008;

	htif_tohost(64, 1, (long) hello, sizeof(hello));

	write_csr(mie, MIP_MTIP);
	*mtimecmp = *mtime + 138727004;
}
