ASM=i686-elf-as
CC=i686-elf-gcc
BINDIR=bin/
KERNEL=$(BINDIR)/mini.bin
CFLAGS=-std=gnu99 -ffreestanding -g

all: $(KERNEL)

$(KERNEL): $(BINDIR)/start.o $(BINDIR)/kernel.o linker.ld
	$(CC) $(CFLAGS) -T linker.ld "$(BINDIR)/start.o" "$(BINDIR)/kernel.o" -o $(KERNEL) -lgcc

$(BINDIR)/start.o: start.s
	$(ASM) start.s -o "$(BINDIR)/start.o"

$(BINDIR)/kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o "$(BINDIR)/kernel.o"

clean:
	rm -rf bin/*
