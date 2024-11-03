set -x

export LIBRARY_PATH="/usr/i686-elf/lib/"
ASM=i686-elf-as
CC=i686-elf-gcc
BINDIR="bin/"
ISODIR="iso/"
KERNEL="${BINDIR}/mini.bin"
ISOKERNEL="${ISODIR}/root/boot/mini.bin"
ISO="${ISODIR}/mini.iso"

${ASM} start.s -o "${BINDIR}/start.o" &&
    ${CC} -std=gnu99 -ffreestanding -g -c kernel.c -o "${BINDIR}/kernel.o" &&
    ${CC} -std=gnu99 -ffreestanding -nostdlib -g -T linker.ld "${BINDIR}/start.o" "${BINDIR}/kernel.o" -o ${KERNEL} -lgcc &&
    cp ${KERNEL} ${ISOKERNEL}

if grub-file --is-x86-multiboot ${ISOKERNEL}; then
   grub-mkrescue iso/root -o ${ISO} && exec qemu-system-i386 ${ISO}
fi
