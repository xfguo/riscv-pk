TARGET=riscv64-unknown-elf
CC=$(TARGET)-gcc
LD=$(TARGET)-gcc
CFLAGS=-Wall -Wextra -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-align -Wsign-compare -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wunused -I. -fomit-frame-pointer -fno-strict-aliasing -fno-builtin -D__gracefulExit -fPIC
LDFLAGS	 = -T ../pk/pk.lds -nostartfiles -static -nostdlib
all:
	$(CC) $(CFLAGS) -o configstring.o -c configstring.c 
	$(CC) $(CFLAGS) -o minit.o        -c minit.c        
	$(CC) $(CFLAGS) -o mtrap.o        -c mtrap.c        
	$(CC) $(CFLAGS) -o mentry.o       -c mentry.S       
	$(LD) $(LDFLAGS) $(LIBS) configstring.o minit.o mtrap.o mentry.o -o m.elf

clean:
	rm -rf m.elf *.o
