#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "This code should not be compiled with a OS-specific compiler"
#elif !defined(__i386__)
#error "This code should be compiled with an x86-elf compiler"
#endif

volatile uint16_t *vga_buffer = (uint16_t *)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F;	/* Black background, White foreground */

#define VGA_BUFFER_CHAR(char) (((uint16_t)term_color << 8) | (char))

void term_init()
{
	for (int i = 0; i < VGA_COLS; i++) {
		for (int j = 0; j < VGA_ROWS; j++) {
			const size_t index = (VGA_COLS * j) + i;
			vga_buffer[index] = VGA_BUFFER_CHAR(' ');
		}
	}
}

void term_putc(char c)
{
	switch (c) {
	case '\n':
		term_col = 0;
		term_row++;
		break;
	default:
		vga_buffer[VGA_COLS * term_row + term_col++] =
			VGA_BUFFER_CHAR(c);
		break;
	}

	if (term_col >= VGA_COLS) {
		term_col = 0;
		term_row++;
	}
}

void term_print(const char *str, size_t lim)
{
	for (size_t i = 0; str[i] != '\0' && i < lim; i++)
		term_putc(str[i]);
}

void kernel_main()
{
	term_init();
	term_print("Hello, World!\n",sizeof("Hello, World!\n"));
}
