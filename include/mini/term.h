#ifndef __MINI_TERM_H
#define __MINI_TERM_H

#include <stddef.h>

void term_init();
void term_putc(char c);
void term_write(const char *str, size_t lim);
void term_println(const char *str);

#endif
