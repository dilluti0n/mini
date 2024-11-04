ARCH=i386
ASM=i686-elf-as
CC=i686-elf-gcc
MAKE=make
KERNEL = vminizz

CFLAGS := -std=gnu99 -ffreestanding -g

TOPDIR = $(shell pwd)
OBJDIR = arch/$(ARCH)
LINKER = $(OBJDIR)/linker.ld
CFLAGS += -I$(TOPDIR)/include

C_SRCS = $(wildcard lib/*.c init/*.c arch/$(ARCH)/*.c)
S_SRCS = $(wildcard arch/$(ARCH)/*.s)
OBJS = $(C_SRCS:.c=.o) $(S_SRCS:.s=.o)

.PHONY: all clean

all: $(KERNEL)

$(OBJS):
	$(MAKE) -C $(dir $@) TOPDIR=$(TOPDIR) CC=$(CC) ASM=$(ASM) CFLAGS="$(CFLAGS)"

$(KERNEL): $(OBJS)
	$(CC) $(CFLAGS) -nostdlib -lgcc -T $(LINKER) -o $@ $(OBJS)

clean:
	$(MAKE) -C arch/i386 clean
	$(MAKE) -C lib clean
	$(MAKE) -C init clean
	rm -f $(KERNEL)
