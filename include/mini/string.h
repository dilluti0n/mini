#ifndef __KSTRING_H
#define __KSTRING_H

#ifdef __GNUC__
	#define strlen __builtin_strlen
#else
	#include <stddef.h>
	size_t strlen(const char *s);
#endif

#endif
