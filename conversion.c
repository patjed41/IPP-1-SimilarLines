// autor - Patryk Jędrzejczak

#include "conversion.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Funkcja sprawdzająca czy znak ch jest cyfrą w systemie o bazie base < 17.
// Oczekuje, że litery reprezentujące cyfry większe od 9 są małe.
static bool is_digit(char ch, int base) {
  if (ch >= '0' && ch <= '9')
    return ch - '0' < base;
  else if (ch >= 'a' && ch <= 'f')
    return ch - 'a' + 10 < base;

  return false;
}

// Funkcja sprawdzająca czy słowo str składa się tylko z cyfr w systemie
// o bazie base < 17. Litery reprezentujące cyfry większe od 9 muszą być małe.
static bool has_only_digits(const char *str, int base) {
  for (unsigned int i = 0; i < strlen(str); i++)
    if (!is_digit(str[i], base))
      return false;

  return true;
}

// Funkcja sprawdzająca czy str jest liczbą w systemie szesnastkowym.
// Oczekuje, że pojawiające się litery są małe.
static bool is_hex(const char *str) {
  if (strlen(str) < 2 || str[0] != '0' || str[1] != 'x' ||
      !has_only_digits(str + 2, 16))
    return false;

  errno = 0;
  char *end_ptr;

  strtoull(str + 2, &end_ptr, 16);

  return *end_ptr == '\0' && errno == 0;
}

// Funkcja sprawdzająca czy str jest liczbą w systemie ósemkowym.
static bool is_oct(const char *str) {
  if (str[0] != '0' || !has_only_digits(str + 1, 8))
    return false;

  errno = 0;
  char *end_ptr;

  strtoull(str + 1, &end_ptr, 8);

  return *end_ptr == '\0' && errno == 0;
}

// Funkcja sprawdzająca czy str jest liczbą zmiennoprzecinkową. Oczekuje,
// że pojawiające się litery są małe.
static bool is_float(const char *str) {
  if (!strcmp(str, "nan"))
    return false;

  // Jeśli str jest liczbą zmiennoprzecinkową zapisaną szesnastkowo, to false.
  for (unsigned int i = 0; i < strlen(str); i++)
    if (str[i] == 'x')
      return false;

  char *end_ptr;
  strtold(str, &end_ptr);

  return *end_ptr == '\0';
}

bool is_number(const char *str) {
  return is_hex(str) || is_oct(str) || is_float(str);
}

long double to_float(const char *str) {
  if (is_hex(str))
    return (long double)strtoull(str, NULL, 16);
  else if (is_oct(str))
    return (long double)strtoull(str, NULL, 8);
  else
    return strtold(str, NULL);
}
