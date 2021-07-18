// autor - Patryk Jędrzejczak

#ifndef SIMILAR_LINES_SAFEFUNCTIONS_H
#define SIMILAR_LINES_SAFEFUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>

// Wszystkie poniższe funkcje są zabezpieczone, tzn. kończą działanie programu
// kodem 1, jeśli w trakcie ich wywołania wystąpił błąd krytyczny.

// zabezpieczony malloc
void *safe_malloc(size_t size);

// zabezpieczony realloc
void *safe_realloc(void *memblock, size_t size);

// Zabezpioczene wypisanie liczby n na standardowe wyjście. Jeśli
// space_before_value ma wartość true, funkcja wypiszę spację przed n.
void safe_printf_int(int n, bool space_before_value);

// zapezpieczony printf("\n")
void safe_newline();

#endif /* SIMILAR_LINES_SAFEFUNCTIONS_H */
