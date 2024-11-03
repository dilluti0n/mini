#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define TABWIDTH 8

#define VGA_BUFFER_CHAR(color, char) (((uint16_t)(color) << 8) | (char))

static uint16_t (*term)[VGA_WIDTH] = (uint16_t (*)[VGA_WIDTH])0xB8000;

static char term_x = 0;		/* 0 to VGA_WIDTH - 1 */
static char term_y = 0;		/* 0 to VGA_HEIGHT - 1 */
static uint8_t term_color = 0x0F;	/* Black background, White foreground */

#define TERM_NEWLINE {\
        term_x = 0; \
        term_y++;   \
}

/* Draw the empty screen */
void term_init()
{
	const int max = VGA_WIDTH * VGA_HEIGHT;

	for (int i = 0; i < max; i++)
		((uint16_t *) term)[i] = VGA_BUFFER_CHAR(term_color, ' ');
}

void term_putc(char c)
{
	switch (c) {
	case '\n':
		term_x = 0;
		term_y++;
		break;
	case '\t':
		term_x += TABWIDTH;
		break;
	default:
		term[term_y][term_x++] = VGA_BUFFER_CHAR(term_color, c);
		break;
	}

	if (term_x >= VGA_WIDTH) {
		term_x = 0;
		term_y++;
	}
}

void term_print(const char *str, size_t lim)
{
	for (size_t i = 0; str[i] != '\0' && i < lim; i++)
		term_putc(str[i]);
}

size_t strlen(const char *str)
{
	size_t i;
	for (i = 0; str[i] != '\0'; i++)
		;
	return i;
}

void term_println(const char *str)
{
	term_print(str, strlen(str));
	term_putc('\n');
}

void kernel_main()
{
	term_init();
	term_println("Hello, world!");
	term_println("This is mini with no version...");
	term_println("\tWhat should I do next so?");
}
