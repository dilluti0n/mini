CC := i686-elf-gcc
AS := i686-elf-as

OBJS = start.o term.o

.PHONY: all clean

all: $(OBJS)

start.o: start.s
	$(AS) -c $< -o $@

term.o: term.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
