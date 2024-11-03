#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "This code should not be compiled with a OS-specific compiler"
#elif !defined(__i386__)
#error "This code should be compiled with an x86-elf compiler"
#endif

volatile uint16_t *vga_buffer = (uint16_t *)0xB8000;

#define VGA_COLS 80
#define VGA_ROWS 2

#define VGA_BUFFER_CHAR(color, char) (((uint16_t)(color) << 8) | (char))
#define VGA_BUFFER_INDEX(column, row) (VGA_COLS * (column) + (row))

static int term_col = 0;
static int term_row = 0;
static uint8_t term_color = 0x0F;	/* Black background, White foreground */

void term_init()
{
	for (int i = 0; i < VGA_BUFFER_INDEX(VGA_COLS, VGA_ROWS); i++)
		vga_buffer[i] = VGA_BUFFER_CHAR(term_color, ' ');
}

void term_putc(char c)
{
	switch (c) {
	case '\n':
		term_col = 0;
		term_row++;
		break;
	default:
		vga_buffer[VGA_BUFFER_INDEX(term_col, term_row++)] =
			VGA_BUFFER_CHAR(term_color, c);
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
