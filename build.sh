export LIBRARY_PATH="/usr/i686-elf/lib/"
ASM=i686-elf-as
CC=i686-elf-gcc
BINDIR="bin/"
ISODIR="iso/"
KERNEL="${BINDIR}/mini.bin"
ISOKERNEL="${ISODIR}/root/boot/mini.bin"
ISO="${ISODIR}/mini.iso"

set +x

make &&
    cp ${KERNEL} ${ISOKERNEL} &&
    grub-file --is-x86-multiboot ${ISOKERNEL} &&
    grub-mkrescue iso/root -o ${ISO} && exec qemu-system-i386 ${ISO}
