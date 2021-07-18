// autor - Patryk Jędrzejczak

#ifndef SIMILAR_LINES_INPUT_H
#define SIMILAR_LINES_INPUT_H

#include <stdbool.h>

// Funkcja sprawdzająca, czy wiersz line jest komentarzem.
bool is_comment(const char *line);

// Funkcja sprawdzająca, czy wiersz line nie zawiera żadnego słowa.
bool is_empty(const char *line);

// Funkcja sprawdzająca, czy wiersz line o liczbie znaków line_length zawiera
// niedozwolony znak.
bool has_illegal_char(const char *line, int line_length);

// Funkcja zmieniająca wszystkie wielkie litery w słowie str na małe.
void letters_to_lower(char *str);

#endif /* SIMILAR_LINES_INPUT_H */
