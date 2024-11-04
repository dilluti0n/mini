export LIBRARY_PATH="/usr/i686-elf/lib/"
ASM=i686-elf-as
CC=i686-elf-gcc
ISODIR="iso"
KERNEL=vminizz
ISOKERNEL="${ISODIR}/boot/${KERNEL}"
ISO="mini.iso"

GRUBDIR="${ISODIR}/boot/grub"
GRUBCFG="${GRUBDIR}/grub.cfg"

set -e

make

mkdir -p ${GRUBDIR}
cat > ${GRUBCFG} << EOF
menuentry "mini Operating System" {
  multiboot /boot/${KERNEL}
  boot
}
EOF

cp ${KERNEL} ${ISOKERNEL}
grub-file --is-x86-multiboot ${ISOKERNEL}
grub-mkrescue ${ISODIR} -o ${ISO} && exec qemu-system-i386 ${ISO}
