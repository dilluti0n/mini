export LIBRARY_PATH="/usr/i686-elf/lib/"
ASM=i686-elf-as
CC=i686-elf-gcc
BINDIR="bin"
ISODIR="iso"
KERNEL="${BINDIR}/mini.bin"
ISOKERNEL="${ISODIR}/boot/mini.bin"
ISO="${BINDIR}/mini.iso"

set +x

make &&
    cp ${KERNEL} ${ISOKERNEL} &&
    grub-file --is-x86-multiboot ${ISOKERNEL} &&
    grub-mkrescue ${ISODIR} -o ${ISO} && exec qemu-system-i386 ${ISO}
