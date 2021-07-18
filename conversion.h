// autor - Patryk Jędrzejczak

#ifndef SIMILAR_LINES_CONVERSION_H
#define SIMILAR_LINES_CONVERSION_H

#include <stdbool.h>

// Funkcja sprawdzająca, czy słowo str jest liczbą zgodnie z def. z zadania.
bool is_number(const char *str);

// Funkcja kowertuje słowo str na typ long double. Zakłada, że str jest liczbą
// zgodnie z def. z zadania.
long double to_float(const char *str);

#endif /* SIMILAR_LINES_CONVERSION_H */
