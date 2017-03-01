TARGET=riscv64-unknown-elf
CC=$(TARGET)-gcc
LD=$(TARGET)-gcc
OBJDUMP=$(TARGET)-objdump
CFLAGS=-g -Wall -Wextra -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-align -Wsign-compare -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wunused -I. -fomit-frame-pointer -fno-strict-aliasing -fno-builtin -D__gracefulExit -fPIC
LDFLAGS	 = -T ../pk/pk.lds -nostartfiles -static -nostdlib
all:
	$(CC) $(CFLAGS) -o configstring.o -c configstring.c 
	$(CC) $(CFLAGS) -o minit.o        -c minit.c        
	$(CC) $(CFLAGS) -o mtrap.o        -c mtrap.c        
	$(CC) $(CFLAGS) -o mentry.o       -c mentry.S       
	$(CC) $(CFLAGS) -o tinyprintf.o   -c tinyprintf.c   
	$(LD) $(LDFLAGS) $(LIBS) tinyprintf.o configstring.o minit.o mtrap.o mentry.o -o m.elf
	$(OBJDUMP) -S m.elf > m.dis

sim:
	echo start and connect remote :3333
	spike -H --gdb-port=3333 m.elf

gdb:
	riscv64-unknown-elf-gdb -x gdb.cmd

clean:
	rm -rf m.elf *.o *.dis

