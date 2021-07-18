// autor - Patryk Jędrzejczak

#include "input.h"
#include <string.h>
#include <ctype.h>

bool is_comment(const char *line) {
  return strlen(line) > 0 && line[0] == '#';
}

bool is_empty(const char *line) {
  for (unsigned int i = 0; i < strlen(line); i++)
    if (!isspace(line[i]))
      return false;

  return true;
}

bool has_illegal_char(const char *line, int line_length) {
  // Sprawdzenie, czy wiersz line zawiera znak '\0'.
  if ((int)strlen(line) < line_length)
    return true;

  // Sprawdzenie, czy wiersz line zawiera inny niedozwolony znak.
  for (unsigned int i = 0; i < strlen(line); i++)
    if (!isspace(line[i]) && (line[i] < 33 || line[i] > 126))
      return true;

  return false;
}

void letters_to_lower(char *str) {
  for (unsigned int i = 0; i < strlen(str); i++)
    str[i] = (char)tolower(str[i]);
}
