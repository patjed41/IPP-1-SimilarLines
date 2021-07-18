// autor - Patryk Jędrzejczak

#ifndef SIMILAR_LINES_CMPFLOATS_H
#define SIMILAR_LINES_CMPFLOATS_H

#include <stdbool.h>

// Funkcja porównująca liczby zmiennoprzecinkowe. Zwraca:
//  -1, jeśli d1 < d2
//  1, jeśli d1 > d2
//  0, jeśli d1 == d2
int cmp_floats(long double d1, long double d2);

#endif /* SIMILAR_LINES_CMPFLOATS_H */
