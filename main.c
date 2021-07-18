// Małe zadanie - program similar_lines.
// autor - Patryk Jędrzejczak

#include "conversion.h"
#include "input.h"
#include "mmset.h"

// Poniższa dyrektywa zapewnia działanie funkcji getline.
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
  // Zmienne potrzebne do wywoływania funkcji getline:
  //  line_buffer - bufor
  //  line_buffer_size - rozmiar bufora
  //  line_size - długość wczytanego wiersza
  char *line_buffer = NULL;
  size_t line_buffer_size = 0;
  int line_size = 0;

  // Numer ostatnio wczytanego wiersza.
  int current_line = 0;

  // Ograniczniki do podziału wiersza na słowa przez funkcję strtok.
  const char *delimiters = " \t\n\v\f\r";

  // Multizbiór wierszy, gdzie każdy wiersz jest multizbiorem typu Mset.
  MMset *mset_of_lines = mmset_new();

  while ((line_size = getline(&line_buffer, &line_buffer_size, stdin)) != -1) {
    current_line++;

    // Sprawdzenie, czy wiersz jest do zignorowania.
    if (is_comment(line_buffer) || is_empty(line_buffer)) {
      continue;
    }

    // Sprawdzenie, czy wiersz zawiera niedozwolony znak.
    if (has_illegal_char(line_buffer, line_size)) {
      if (fprintf(stderr, "ERROR %d\n", current_line) < 0)
        exit(1);
      continue;
    }

    // Utworzonie nowego multizbioru reprezentującego aktualny wiersz.
    mmset_add_mset(mset_of_lines, current_line);

    letters_to_lower(line_buffer);

    // Aktualnie rozpatrywane słowo.
    char *word = strtok(line_buffer, delimiters);

    // Dodanie wszystkich liczb i nieliczb z wiersza do nowego multizbioru.
    while (word != NULL) {
      if (is_number(word))
        mmset_add_float_to_last_mset(mset_of_lines, to_float(word));
      else
        mmset_add_string_to_last_mset(mset_of_lines, word);

      word = strtok(NULL, delimiters);
    }

    errno = 0;
  }

  // Sprawdzenie, czy ostatnie wywołanie funkcji getline zakończyło się błędem.
  if (errno != 0)
    exit(1);

  mmset_sort(mset_of_lines);
  mmset_print(*mset_of_lines);
  mmset_destroy(mset_of_lines);

  free(line_buffer);

  return 0;
}
