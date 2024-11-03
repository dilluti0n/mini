#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define TABWIDTH 8

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

struct term_position {
	char x;
	char y;
};

typedef uint16_t (*term_t)[VGA_WIDTH];

static struct term_position current;
static uint16_t term_color;
static term_t term;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
static inline uint16_t vga_entry(uint8_t color, unsigned char c);
static inline void term_newline();
static void term_scroll();
static void term_current_setx(int x);
static void term_current_sety(int y);

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(uint8_t color, unsigned char c)
{
	return (uint16_t)c | (uint16_t)color << 8;
}

static inline void term_newline()
{
	current.x = 0;

	/* prevent assigning zero twice to current.x */
	if (++current.y >= VGA_HEIGHT) {
		term_scroll();
		current.y = VGA_HEIGHT - 1;
	}
}

static void term_scroll()
{
	const int height = VGA_HEIGHT - 1;
	int x;

	for (x = 0; x < height; x++)
		for (int y = 0; y < VGA_WIDTH; y++)
			term[x][y] = term[x + 1][y];

	for (int y = 0; y < VGA_WIDTH; y++)
		term[x][y] = vga_entry(term_color, ' ');
}

static void term_current_setx(int x)
{
	if ((current.x = x) >= VGA_WIDTH)
		term_newline();
}

static void term_current_sety(int y)
{
	if ((current.y = y) >= VGA_HEIGHT) {
		term_scroll();
		current.x = 0;
		current.y = VGA_HEIGHT - 1;
	}
}

/* Draw the empty screen */
void term_init()
{
	current.x = 0;
	current.y = 0;
	term_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	term = (term_t)0xB8000;

	const int max = VGA_WIDTH * VGA_HEIGHT;
	for (int i = 0; i < max; i++)
		((uint16_t *) term)[i] = vga_entry(term_color, ' ');
}

void term_putc(char c)
{
	int tmp;

	switch (c) {
	case '\n':
		term_newline();
		break;
	case '\t':
		/* TODO: multiple newline by \t */
		term_current_setx((current.x + TABWIDTH) & ~(TABWIDTH - 1));
		break;
	default:
		term[current.y][(tmp = current.x)] = vga_entry(term_color, c);
		term_current_setx(tmp + 1);
		break;
	}
}

void term_write(const char *str, size_t lim)
{
	for (size_t i = 0; i < lim; i++)
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
	term_write(str, strlen(str));
	term_newline();
}

void kernel_main()
{
	term_init();
	term_println("This is mini with version...");
	term_println("so...\tWhat should I do next??\t\t\t\t");
	term_println("testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttest");
}
